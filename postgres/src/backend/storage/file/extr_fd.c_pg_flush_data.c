#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ ENOSYS ; 
 int FATAL ; 
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MS_ASYNC ; 
 int /*<<< orphan*/  POSIX_FADV_DONTNEED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  SYNC_FILE_RANGE_WRITE ; 
 int WARNING ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int data_sync_elevel (int) ; 
 int /*<<< orphan*/  enableFsync ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int msync (void*,size_t,int /*<<< orphan*/ ) ; 
 int munmap (void*,size_t) ; 
 int posix_fadvise (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int sync_file_range (int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

void
pg_flush_data(int fd, off_t offset, off_t nbytes)
{
	/*
	 * Right now file flushing is primarily used to avoid making later
	 * fsync()/fdatasync() calls have less impact. Thus don't trigger flushes
	 * if fsyncs are disabled - that's a decision we might want to make
	 * configurable at some point.
	 */
	if (!enableFsync)
		return;

	/*
	 * We compile all alternatives that are supported on the current platform,
	 * to find portability problems more easily.
	 */
#if defined(HAVE_SYNC_FILE_RANGE)
	{
		int			rc;
		static bool not_implemented_by_kernel = false;

		if (not_implemented_by_kernel)
			return;

		/*
		 * sync_file_range(SYNC_FILE_RANGE_WRITE), currently linux specific,
		 * tells the OS that writeback for the specified blocks should be
		 * started, but that we don't want to wait for completion.  Note that
		 * this call might block if too much dirty data exists in the range.
		 * This is the preferable method on OSs supporting it, as it works
		 * reliably when available (contrast to msync()) and doesn't flush out
		 * clean data (like FADV_DONTNEED).
		 */
		rc = sync_file_range(fd, offset, nbytes,
							 SYNC_FILE_RANGE_WRITE);
		if (rc != 0)
		{
			int			elevel;

			/*
			 * For systems that don't have an implementation of
			 * sync_file_range() such as Windows WSL, generate only one
			 * warning and then suppress all further attempts by this process.
			 */
			if (errno == ENOSYS)
			{
				elevel = WARNING;
				not_implemented_by_kernel = true;
			}
			else
				elevel = data_sync_elevel(WARNING);

			ereport(elevel,
					(errcode_for_file_access(),
					 errmsg("could not flush dirty data: %m")));
		}

		return;
	}
#endif
#if !defined(WIN32) && defined(MS_ASYNC)
	{
		void	   *p;
		static int	pagesize = 0;

		/*
		 * On several OSs msync(MS_ASYNC) on a mmap'ed file triggers
		 * writeback. On linux it only does so if MS_SYNC is specified, but
		 * then it does the writeback synchronously. Luckily all common linux
		 * systems have sync_file_range().  This is preferable over
		 * FADV_DONTNEED because it doesn't flush out clean data.
		 *
		 * We map the file (mmap()), tell the kernel to sync back the contents
		 * (msync()), and then remove the mapping again (munmap()).
		 */

		/* mmap() needs actual length if we want to map whole file */
		if (offset == 0 && nbytes == 0)
		{
			nbytes = lseek(fd, 0, SEEK_END);
			if (nbytes < 0)
			{
				ereport(WARNING,
						(errcode_for_file_access(),
						 errmsg("could not determine dirty data size: %m")));
				return;
			}
		}

		/*
		 * Some platforms reject partial-page mmap() attempts.  To deal with
		 * that, just truncate the request to a page boundary.  If any extra
		 * bytes don't get flushed, well, it's only a hint anyway.
		 */

		/* fetch pagesize only once */
		if (pagesize == 0)
			pagesize = sysconf(_SC_PAGESIZE);

		/* align length to pagesize, dropping any fractional page */
		if (pagesize > 0)
			nbytes = (nbytes / pagesize) * pagesize;

		/* fractional-page request is a no-op */
		if (nbytes <= 0)
			return;

		/*
		 * mmap could well fail, particularly on 32-bit platforms where there
		 * may simply not be enough address space.  If so, silently fall
		 * through to the next implementation.
		 */
		if (nbytes <= (off_t) SSIZE_MAX)
			p = mmap(NULL, nbytes, PROT_READ, MAP_SHARED, fd, offset);
		else
			p = MAP_FAILED;

		if (p != MAP_FAILED)
		{
			int			rc;

			rc = msync(p, (size_t) nbytes, MS_ASYNC);
			if (rc != 0)
			{
				ereport(data_sync_elevel(WARNING),
						(errcode_for_file_access(),
						 errmsg("could not flush dirty data: %m")));
				/* NB: need to fall through to munmap()! */
			}

			rc = munmap(p, (size_t) nbytes);
			if (rc != 0)
			{
				/* FATAL error because mapping would remain */
				ereport(FATAL,
						(errcode_for_file_access(),
						 errmsg("could not munmap() while flushing data: %m")));
			}

			return;
		}
	}
#endif
#if defined(USE_POSIX_FADVISE) && defined(POSIX_FADV_DONTNEED)
	{
		int			rc;

		/*
		 * Signal the kernel that the passed in range should not be cached
		 * anymore. This has the, desired, side effect of writing out dirty
		 * data, and the, undesired, side effect of likely discarding useful
		 * clean cached blocks.  For the latter reason this is the least
		 * preferable method.
		 */

		rc = posix_fadvise(fd, offset, nbytes, POSIX_FADV_DONTNEED);

		if (rc != 0)
		{
			/* don't error out, this is just a performance optimization */
			ereport(WARNING,
					(errcode_for_file_access(),
					 errmsg("could not flush dirty data: %m")));
		}

		return;
	}
#endif
}