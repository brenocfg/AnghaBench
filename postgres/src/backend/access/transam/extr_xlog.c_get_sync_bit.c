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

/* Variables and functions */
 int /*<<< orphan*/  AmWalReceiverProcess () ; 
 int /*<<< orphan*/  ERROR ; 
 int OPEN_DATASYNC_FLAG ; 
 int OPEN_SYNC_FLAG ; 
 int PG_O_DIRECT ; 
#define  SYNC_METHOD_FDATASYNC 132 
#define  SYNC_METHOD_FSYNC 131 
#define  SYNC_METHOD_FSYNC_WRITETHROUGH 130 
#define  SYNC_METHOD_OPEN 129 
#define  SYNC_METHOD_OPEN_DSYNC 128 
 int /*<<< orphan*/  XLogIsNeeded () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enableFsync ; 

__attribute__((used)) static int
get_sync_bit(int method)
{
	int			o_direct_flag = 0;

	/* If fsync is disabled, never open in sync mode */
	if (!enableFsync)
		return 0;

	/*
	 * Optimize writes by bypassing kernel cache with O_DIRECT when using
	 * O_SYNC/O_FSYNC and O_DSYNC.  But only if archiving and streaming are
	 * disabled, otherwise the archive command or walsender process will read
	 * the WAL soon after writing it, which is guaranteed to cause a physical
	 * read if we bypassed the kernel cache. We also skip the
	 * posix_fadvise(POSIX_FADV_DONTNEED) call in XLogFileClose() for the same
	 * reason.
	 *
	 * Never use O_DIRECT in walreceiver process for similar reasons; the WAL
	 * written by walreceiver is normally read by the startup process soon
	 * after its written. Also, walreceiver performs unaligned writes, which
	 * don't work with O_DIRECT, so it is required for correctness too.
	 */
	if (!XLogIsNeeded() && !AmWalReceiverProcess())
		o_direct_flag = PG_O_DIRECT;

	switch (method)
	{
			/*
			 * enum values for all sync options are defined even if they are
			 * not supported on the current platform.  But if not, they are
			 * not included in the enum option array, and therefore will never
			 * be seen here.
			 */
		case SYNC_METHOD_FSYNC:
		case SYNC_METHOD_FSYNC_WRITETHROUGH:
		case SYNC_METHOD_FDATASYNC:
			return 0;
#ifdef OPEN_SYNC_FLAG
		case SYNC_METHOD_OPEN:
			return OPEN_SYNC_FLAG | o_direct_flag;
#endif
#ifdef OPEN_DATASYNC_FLAG
		case SYNC_METHOD_OPEN_DSYNC:
			return OPEN_DATASYNC_FLAG | o_direct_flag;
#endif
		default:
			/* can't happen (unless we are out of sync with option array) */
			elog(ERROR, "unrecognized wal_sync_method: %d", method);
			return 0;			/* silence warning */
	}
}