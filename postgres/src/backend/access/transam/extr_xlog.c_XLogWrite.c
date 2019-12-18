#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ pg_time_t ;
struct TYPE_7__ {int Write; int Flush; } ;
typedef  TYPE_2__ XLogwrtRqst ;
typedef  int XLogRecPtr ;
struct TYPE_9__ {int Write; int Flush; } ;
struct TYPE_6__ {int Write; int Flush; } ;
struct TYPE_8__ {int* xlblocks; int XLogCacheBlck; char* pages; int lastSegSwitchLSN; int /*<<< orphan*/  info_lck; TYPE_1__ LogwrtRqst; TYPE_5__ LogwrtResult; scalar_t__ lastSegSwitchTime; } ;
typedef  int Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHECKPOINT_CAUSE_XLOG ; 
 scalar_t__ CritSectionCount ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GetRedoRecPtr () ; 
 scalar_t__ IsUnderPostmaster ; 
 TYPE_5__ LogwrtResult ; 
 int NextBufIdx (int) ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  RequestCheckpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ SYNC_METHOD_OPEN ; 
 scalar_t__ SYNC_METHOD_OPEN_DSYNC ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_WRITE ; 
 int /*<<< orphan*/  WalSndWakeupRequest () ; 
 int /*<<< orphan*/  XLByteInPrevSeg (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XLByteToPrevSeg (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogArchiveNotifySeg (int /*<<< orphan*/ ) ; 
 scalar_t__ XLogArchivingActive () ; 
 scalar_t__ XLogCheckpointNeeded (int /*<<< orphan*/ ) ; 
 TYPE_4__* XLogCtl ; 
 int /*<<< orphan*/  XLogFileClose () ; 
 scalar_t__ XLogFileInit (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  XLogFileNameP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XLogFileOpen (int /*<<< orphan*/ ) ; 
 int XLogRecPtrToBufIdx (int) ; 
 scalar_t__ XLogSegmentOffset (int,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  issue_xlog_fsync (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ openLogFile ; 
 int /*<<< orphan*/  openLogSegNo ; 
 int pg_pwrite (scalar_t__,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  pgstat_report_wait_end () ; 
 int /*<<< orphan*/  pgstat_report_wait_start (int /*<<< orphan*/ ) ; 
 scalar_t__ sync_method ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ wal_segment_size ; 

__attribute__((used)) static void
XLogWrite(XLogwrtRqst WriteRqst, bool flexible)
{
	bool		ispartialpage;
	bool		last_iteration;
	bool		finishing_seg;
	bool		use_existent;
	int			curridx;
	int			npages;
	int			startidx;
	uint32		startoffset;

	/* We should always be inside a critical section here */
	Assert(CritSectionCount > 0);

	/*
	 * Update local LogwrtResult (caller probably did this already, but...)
	 */
	LogwrtResult = XLogCtl->LogwrtResult;

	/*
	 * Since successive pages in the xlog cache are consecutively allocated,
	 * we can usually gather multiple pages together and issue just one
	 * write() call.  npages is the number of pages we have determined can be
	 * written together; startidx is the cache block index of the first one,
	 * and startoffset is the file offset at which it should go. The latter
	 * two variables are only valid when npages > 0, but we must initialize
	 * all of them to keep the compiler quiet.
	 */
	npages = 0;
	startidx = 0;
	startoffset = 0;

	/*
	 * Within the loop, curridx is the cache block index of the page to
	 * consider writing.  Begin at the buffer containing the next unwritten
	 * page, or last partially written page.
	 */
	curridx = XLogRecPtrToBufIdx(LogwrtResult.Write);

	while (LogwrtResult.Write < WriteRqst.Write)
	{
		/*
		 * Make sure we're not ahead of the insert process.  This could happen
		 * if we're passed a bogus WriteRqst.Write that is past the end of the
		 * last page that's been initialized by AdvanceXLInsertBuffer.
		 */
		XLogRecPtr	EndPtr = XLogCtl->xlblocks[curridx];

		if (LogwrtResult.Write >= EndPtr)
			elog(PANIC, "xlog write request %X/%X is past end of log %X/%X",
				 (uint32) (LogwrtResult.Write >> 32),
				 (uint32) LogwrtResult.Write,
				 (uint32) (EndPtr >> 32), (uint32) EndPtr);

		/* Advance LogwrtResult.Write to end of current buffer page */
		LogwrtResult.Write = EndPtr;
		ispartialpage = WriteRqst.Write < LogwrtResult.Write;

		if (!XLByteInPrevSeg(LogwrtResult.Write, openLogSegNo,
							 wal_segment_size))
		{
			/*
			 * Switch to new logfile segment.  We cannot have any pending
			 * pages here (since we dump what we have at segment end).
			 */
			Assert(npages == 0);
			if (openLogFile >= 0)
				XLogFileClose();
			XLByteToPrevSeg(LogwrtResult.Write, openLogSegNo,
							wal_segment_size);

			/* create/use new log file */
			use_existent = true;
			openLogFile = XLogFileInit(openLogSegNo, &use_existent, true);
		}

		/* Make sure we have the current logfile open */
		if (openLogFile < 0)
		{
			XLByteToPrevSeg(LogwrtResult.Write, openLogSegNo,
							wal_segment_size);
			openLogFile = XLogFileOpen(openLogSegNo);
		}

		/* Add current page to the set of pending pages-to-dump */
		if (npages == 0)
		{
			/* first of group */
			startidx = curridx;
			startoffset = XLogSegmentOffset(LogwrtResult.Write - XLOG_BLCKSZ,
											wal_segment_size);
		}
		npages++;

		/*
		 * Dump the set if this will be the last loop iteration, or if we are
		 * at the last page of the cache area (since the next page won't be
		 * contiguous in memory), or if we are at the end of the logfile
		 * segment.
		 */
		last_iteration = WriteRqst.Write <= LogwrtResult.Write;

		finishing_seg = !ispartialpage &&
			(startoffset + npages * XLOG_BLCKSZ) >= wal_segment_size;

		if (last_iteration ||
			curridx == XLogCtl->XLogCacheBlck ||
			finishing_seg)
		{
			char	   *from;
			Size		nbytes;
			Size		nleft;
			int			written;

			/* OK to write the page(s) */
			from = XLogCtl->pages + startidx * (Size) XLOG_BLCKSZ;
			nbytes = npages * (Size) XLOG_BLCKSZ;
			nleft = nbytes;
			do
			{
				errno = 0;
				pgstat_report_wait_start(WAIT_EVENT_WAL_WRITE);
				written = pg_pwrite(openLogFile, from, nleft, startoffset);
				pgstat_report_wait_end();
				if (written <= 0)
				{
					if (errno == EINTR)
						continue;
					ereport(PANIC,
							(errcode_for_file_access(),
							 errmsg("could not write to log file %s "
									"at offset %u, length %zu: %m",
									XLogFileNameP(ThisTimeLineID, openLogSegNo),
									startoffset, nleft)));
				}
				nleft -= written;
				from += written;
				startoffset += written;
			} while (nleft > 0);

			npages = 0;

			/*
			 * If we just wrote the whole last page of a logfile segment,
			 * fsync the segment immediately.  This avoids having to go back
			 * and re-open prior segments when an fsync request comes along
			 * later. Doing it here ensures that one and only one backend will
			 * perform this fsync.
			 *
			 * This is also the right place to notify the Archiver that the
			 * segment is ready to copy to archival storage, and to update the
			 * timer for archive_timeout, and to signal for a checkpoint if
			 * too many logfile segments have been used since the last
			 * checkpoint.
			 */
			if (finishing_seg)
			{
				issue_xlog_fsync(openLogFile, openLogSegNo);

				/* signal that we need to wakeup walsenders later */
				WalSndWakeupRequest();

				LogwrtResult.Flush = LogwrtResult.Write;	/* end of page */

				if (XLogArchivingActive())
					XLogArchiveNotifySeg(openLogSegNo);

				XLogCtl->lastSegSwitchTime = (pg_time_t) time(NULL);
				XLogCtl->lastSegSwitchLSN = LogwrtResult.Flush;

				/*
				 * Request a checkpoint if we've consumed too much xlog since
				 * the last one.  For speed, we first check using the local
				 * copy of RedoRecPtr, which might be out of date; if it looks
				 * like a checkpoint is needed, forcibly update RedoRecPtr and
				 * recheck.
				 */
				if (IsUnderPostmaster && XLogCheckpointNeeded(openLogSegNo))
				{
					(void) GetRedoRecPtr();
					if (XLogCheckpointNeeded(openLogSegNo))
						RequestCheckpoint(CHECKPOINT_CAUSE_XLOG);
				}
			}
		}

		if (ispartialpage)
		{
			/* Only asked to write a partial page */
			LogwrtResult.Write = WriteRqst.Write;
			break;
		}
		curridx = NextBufIdx(curridx);

		/* If flexible, break out of loop as soon as we wrote something */
		if (flexible && npages == 0)
			break;
	}

	Assert(npages == 0);

	/*
	 * If asked to flush, do so
	 */
	if (LogwrtResult.Flush < WriteRqst.Flush &&
		LogwrtResult.Flush < LogwrtResult.Write)

	{
		/*
		 * Could get here without iterating above loop, in which case we might
		 * have no open file or the wrong one.  However, we do not need to
		 * fsync more than one file.
		 */
		if (sync_method != SYNC_METHOD_OPEN &&
			sync_method != SYNC_METHOD_OPEN_DSYNC)
		{
			if (openLogFile >= 0 &&
				!XLByteInPrevSeg(LogwrtResult.Write, openLogSegNo,
								 wal_segment_size))
				XLogFileClose();
			if (openLogFile < 0)
			{
				XLByteToPrevSeg(LogwrtResult.Write, openLogSegNo,
								wal_segment_size);
				openLogFile = XLogFileOpen(openLogSegNo);
			}

			issue_xlog_fsync(openLogFile, openLogSegNo);
		}

		/* signal that we need to wakeup walsenders later */
		WalSndWakeupRequest();

		LogwrtResult.Flush = LogwrtResult.Write;
	}

	/*
	 * Update shared-memory status
	 *
	 * We make sure that the shared 'request' values do not fall behind the
	 * 'result' values.  This is not absolutely essential, but it saves some
	 * code in a couple of places.
	 */
	{
		SpinLockAcquire(&XLogCtl->info_lck);
		XLogCtl->LogwrtResult = LogwrtResult;
		if (XLogCtl->LogwrtRqst.Write < LogwrtResult.Write)
			XLogCtl->LogwrtRqst.Write = LogwrtResult.Write;
		if (XLogCtl->LogwrtRqst.Flush < LogwrtResult.Flush)
			XLogCtl->LogwrtRqst.Flush = LogwrtResult.Flush;
		SpinLockRelease(&XLogCtl->info_lck);
	}
}