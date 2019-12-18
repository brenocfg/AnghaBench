#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_9__ {scalar_t__ do_fsync; TYPE_1__* shared; } ;
struct TYPE_8__ {int num_files; int* segno; int* fd; } ;
struct TYPE_7__ {scalar_t__* group_lsn; int lsn_groups_per_page; int /*<<< orphan*/ * page_buffer; } ;
typedef  TYPE_1__* SlruShared ;
typedef  TYPE_2__* SlruFlush ;
typedef  TYPE_3__* SlruCtl ;

/* Variables and functions */
 int BLCKSZ ; 
 scalar_t__ CloseTransientFile (int) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 scalar_t__ ENOSPC ; 
 int MAXPGPATH ; 
 int MAX_FLUSH_BUFFERS ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int OpenTransientFile (char*,int) ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SLRU_CLOSE_FAILED ; 
 int /*<<< orphan*/  SLRU_FSYNC_FAILED ; 
 int /*<<< orphan*/  SLRU_OPEN_FAILED ; 
 int SLRU_PAGES_PER_SEGMENT ; 
 int /*<<< orphan*/  SLRU_SEEK_FAILED ; 
 int /*<<< orphan*/  SLRU_WRITE_FAILED ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SlruFileName (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  WAIT_EVENT_SLRU_SYNC ; 
 int /*<<< orphan*/  WAIT_EVENT_SLRU_WRITE ; 
 int /*<<< orphan*/  XLogFlush (scalar_t__) ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_fsync (int) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slru_errcause ; 
 scalar_t__ slru_errno ; 
 int write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
SlruPhysicalWritePage(SlruCtl ctl, int pageno, int slotno, SlruFlush fdata)
{
	SlruShared	shared = ctl->shared;
	int			segno = pageno / SLRU_PAGES_PER_SEGMENT;
	int			rpageno = pageno % SLRU_PAGES_PER_SEGMENT;
	int			offset = rpageno * BLCKSZ;
	char		path[MAXPGPATH];
	int			fd = -1;

	/*
	 * Honor the write-WAL-before-data rule, if appropriate, so that we do not
	 * write out data before associated WAL records.  This is the same action
	 * performed during FlushBuffer() in the main buffer manager.
	 */
	if (shared->group_lsn != NULL)
	{
		/*
		 * We must determine the largest async-commit LSN for the page. This
		 * is a bit tedious, but since this entire function is a slow path
		 * anyway, it seems better to do this here than to maintain a per-page
		 * LSN variable (which'd need an extra comparison in the
		 * transaction-commit path).
		 */
		XLogRecPtr	max_lsn;
		int			lsnindex,
					lsnoff;

		lsnindex = slotno * shared->lsn_groups_per_page;
		max_lsn = shared->group_lsn[lsnindex++];
		for (lsnoff = 1; lsnoff < shared->lsn_groups_per_page; lsnoff++)
		{
			XLogRecPtr	this_lsn = shared->group_lsn[lsnindex++];

			if (max_lsn < this_lsn)
				max_lsn = this_lsn;
		}

		if (!XLogRecPtrIsInvalid(max_lsn))
		{
			/*
			 * As noted above, elog(ERROR) is not acceptable here, so if
			 * XLogFlush were to fail, we must PANIC.  This isn't much of a
			 * restriction because XLogFlush is just about all critical
			 * section anyway, but let's make sure.
			 */
			START_CRIT_SECTION();
			XLogFlush(max_lsn);
			END_CRIT_SECTION();
		}
	}

	/*
	 * During a Flush, we may already have the desired file open.
	 */
	if (fdata)
	{
		int			i;

		for (i = 0; i < fdata->num_files; i++)
		{
			if (fdata->segno[i] == segno)
			{
				fd = fdata->fd[i];
				break;
			}
		}
	}

	if (fd < 0)
	{
		/*
		 * If the file doesn't already exist, we should create it.  It is
		 * possible for this to need to happen when writing a page that's not
		 * first in its segment; we assume the OS can cope with that. (Note:
		 * it might seem that it'd be okay to create files only when
		 * SimpleLruZeroPage is called for the first page of a segment.
		 * However, if after a crash and restart the REDO logic elects to
		 * replay the log from a checkpoint before the latest one, then it's
		 * possible that we will get commands to set transaction status of
		 * transactions that have already been truncated from the commit log.
		 * Easiest way to deal with that is to accept references to
		 * nonexistent files here and in SlruPhysicalReadPage.)
		 *
		 * Note: it is possible for more than one backend to be executing this
		 * code simultaneously for different pages of the same file. Hence,
		 * don't use O_EXCL or O_TRUNC or anything like that.
		 */
		SlruFileName(ctl, path, segno);
		fd = OpenTransientFile(path, O_RDWR | O_CREAT | PG_BINARY);
		if (fd < 0)
		{
			slru_errcause = SLRU_OPEN_FAILED;
			slru_errno = errno;
			return false;
		}

		if (fdata)
		{
			if (fdata->num_files < MAX_FLUSH_BUFFERS)
			{
				fdata->fd[fdata->num_files] = fd;
				fdata->segno[fdata->num_files] = segno;
				fdata->num_files++;
			}
			else
			{
				/*
				 * In the unlikely event that we exceed MAX_FLUSH_BUFFERS,
				 * fall back to treating it as a standalone write.
				 */
				fdata = NULL;
			}
		}
	}

	if (lseek(fd, (off_t) offset, SEEK_SET) < 0)
	{
		slru_errcause = SLRU_SEEK_FAILED;
		slru_errno = errno;
		if (!fdata)
			CloseTransientFile(fd);
		return false;
	}

	errno = 0;
	pgstat_report_wait_start(WAIT_EVENT_SLRU_WRITE);
	if (write(fd, shared->page_buffer[slotno], BLCKSZ) != BLCKSZ)
	{
		pgstat_report_wait_end();
		/* if write didn't set errno, assume problem is no disk space */
		if (errno == 0)
			errno = ENOSPC;
		slru_errcause = SLRU_WRITE_FAILED;
		slru_errno = errno;
		if (!fdata)
			CloseTransientFile(fd);
		return false;
	}
	pgstat_report_wait_end();

	/*
	 * If not part of Flush, need to fsync now.  We assume this happens
	 * infrequently enough that it's not a performance issue.
	 */
	if (!fdata)
	{
		pgstat_report_wait_start(WAIT_EVENT_SLRU_SYNC);
		if (ctl->do_fsync && pg_fsync(fd) != 0)
		{
			pgstat_report_wait_end();
			slru_errcause = SLRU_FSYNC_FAILED;
			slru_errno = errno;
			CloseTransientFile(fd);
			return false;
		}
		pgstat_report_wait_end();

		if (CloseTransientFile(fd) != 0)
		{
			slru_errcause = SLRU_CLOSE_FAILED;
			slru_errno = errno;
			return false;
		}
	}

	return true;
}