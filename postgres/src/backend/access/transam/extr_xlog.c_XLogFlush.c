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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_7__ {int Write; int Flush; } ;
typedef  TYPE_2__ XLogwrtRqst ;
typedef  int XLogRecPtr ;
struct TYPE_9__ {int Flush; int Write; } ;
struct TYPE_6__ {int Write; } ;
struct TYPE_8__ {TYPE_5__ LogwrtResult; int /*<<< orphan*/  info_lck; TYPE_1__ LogwrtRqst; } ;

/* Variables and functions */
 scalar_t__ CommitDelay ; 
 int /*<<< orphan*/  CommitSiblings ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LWLockAcquireOrWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_5__ LogwrtResult ; 
 scalar_t__ MinimumActiveBackends (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateMinRecoveryPoint (int,int) ; 
 int /*<<< orphan*/  WALWriteLock ; 
 int WaitXLogInsertionsToFinish (int) ; 
 int /*<<< orphan*/  WalSndWakeupProcessRequests () ; 
 scalar_t__ XLOG_DEBUG ; 
 TYPE_4__* XLogCtl ; 
 int /*<<< orphan*/  XLogInsertAllowed () ; 
 int /*<<< orphan*/  XLogWrite (TYPE_2__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ enableFsync ; 
 int /*<<< orphan*/  pg_usleep (scalar_t__) ; 

void
XLogFlush(XLogRecPtr record)
{
	XLogRecPtr	WriteRqstPtr;
	XLogwrtRqst WriteRqst;

	/*
	 * During REDO, we are reading not writing WAL.  Therefore, instead of
	 * trying to flush the WAL, we should update minRecoveryPoint instead. We
	 * test XLogInsertAllowed(), not InRecovery, because we need checkpointer
	 * to act this way too, and because when it tries to write the
	 * end-of-recovery checkpoint, it should indeed flush.
	 */
	if (!XLogInsertAllowed())
	{
		UpdateMinRecoveryPoint(record, false);
		return;
	}

	/* Quick exit if already known flushed */
	if (record <= LogwrtResult.Flush)
		return;

#ifdef WAL_DEBUG
	if (XLOG_DEBUG)
		elog(LOG, "xlog flush request %X/%X; write %X/%X; flush %X/%X",
			 (uint32) (record >> 32), (uint32) record,
			 (uint32) (LogwrtResult.Write >> 32), (uint32) LogwrtResult.Write,
			 (uint32) (LogwrtResult.Flush >> 32), (uint32) LogwrtResult.Flush);
#endif

	START_CRIT_SECTION();

	/*
	 * Since fsync is usually a horribly expensive operation, we try to
	 * piggyback as much data as we can on each fsync: if we see any more data
	 * entered into the xlog buffer, we'll write and fsync that too, so that
	 * the final value of LogwrtResult.Flush is as large as possible. This
	 * gives us some chance of avoiding another fsync immediately after.
	 */

	/* initialize to given target; may increase below */
	WriteRqstPtr = record;

	/*
	 * Now wait until we get the write lock, or someone else does the flush
	 * for us.
	 */
	for (;;)
	{
		XLogRecPtr	insertpos;

		/* read LogwrtResult and update local state */
		SpinLockAcquire(&XLogCtl->info_lck);
		if (WriteRqstPtr < XLogCtl->LogwrtRqst.Write)
			WriteRqstPtr = XLogCtl->LogwrtRqst.Write;
		LogwrtResult = XLogCtl->LogwrtResult;
		SpinLockRelease(&XLogCtl->info_lck);

		/* done already? */
		if (record <= LogwrtResult.Flush)
			break;

		/*
		 * Before actually performing the write, wait for all in-flight
		 * insertions to the pages we're about to write to finish.
		 */
		insertpos = WaitXLogInsertionsToFinish(WriteRqstPtr);

		/*
		 * Try to get the write lock. If we can't get it immediately, wait
		 * until it's released, and recheck if we still need to do the flush
		 * or if the backend that held the lock did it for us already. This
		 * helps to maintain a good rate of group committing when the system
		 * is bottlenecked by the speed of fsyncing.
		 */
		if (!LWLockAcquireOrWait(WALWriteLock, LW_EXCLUSIVE))
		{
			/*
			 * The lock is now free, but we didn't acquire it yet. Before we
			 * do, loop back to check if someone else flushed the record for
			 * us already.
			 */
			continue;
		}

		/* Got the lock; recheck whether request is satisfied */
		LogwrtResult = XLogCtl->LogwrtResult;
		if (record <= LogwrtResult.Flush)
		{
			LWLockRelease(WALWriteLock);
			break;
		}

		/*
		 * Sleep before flush! By adding a delay here, we may give further
		 * backends the opportunity to join the backlog of group commit
		 * followers; this can significantly improve transaction throughput,
		 * at the risk of increasing transaction latency.
		 *
		 * We do not sleep if enableFsync is not turned on, nor if there are
		 * fewer than CommitSiblings other backends with active transactions.
		 */
		if (CommitDelay > 0 && enableFsync &&
			MinimumActiveBackends(CommitSiblings))
		{
			pg_usleep(CommitDelay);

			/*
			 * Re-check how far we can now flush the WAL. It's generally not
			 * safe to call WaitXLogInsertionsToFinish while holding
			 * WALWriteLock, because an in-progress insertion might need to
			 * also grab WALWriteLock to make progress. But we know that all
			 * the insertions up to insertpos have already finished, because
			 * that's what the earlier WaitXLogInsertionsToFinish() returned.
			 * We're only calling it again to allow insertpos to be moved
			 * further forward, not to actually wait for anyone.
			 */
			insertpos = WaitXLogInsertionsToFinish(insertpos);
		}

		/* try to write/flush later additions to XLOG as well */
		WriteRqst.Write = insertpos;
		WriteRqst.Flush = insertpos;

		XLogWrite(WriteRqst, false);

		LWLockRelease(WALWriteLock);
		/* done */
		break;
	}

	END_CRIT_SECTION();

	/* wake up walsenders now that we've released heavily contended locks */
	WalSndWakeupProcessRequests();

	/*
	 * If we still haven't flushed to the request point then we have a
	 * problem; most likely, the requested flush point is past end of XLOG.
	 * This has been seen to occur when a disk page has a corrupted LSN.
	 *
	 * Formerly we treated this as a PANIC condition, but that hurts the
	 * system's robustness rather than helping it: we do not want to take down
	 * the whole system due to corruption on one data page.  In particular, if
	 * the bad page is encountered again during recovery then we would be
	 * unable to restart the database at all!  (This scenario actually
	 * happened in the field several times with 7.1 releases.)	As of 8.4, bad
	 * LSNs encountered during recovery are UpdateMinRecoveryPoint's problem;
	 * the only time we can reach here during recovery is while flushing the
	 * end-of-recovery checkpoint record, and we don't expect that to have a
	 * bad LSN.
	 *
	 * Note that for calls from xact.c, the ERROR will be promoted to PANIC
	 * since xact.c calls this routine inside a critical section.  However,
	 * calls from bufmgr.c are not within critical sections and so we will not
	 * force a restart for a bad LSN on a data page.
	 */
	if (LogwrtResult.Flush < record)
		elog(ERROR,
			 "xlog flush request %X/%X is not satisfied --- flushed only to %X/%X",
			 (uint32) (record >> 32), (uint32) record,
			 (uint32) (LogwrtResult.Flush >> 32), (uint32) LogwrtResult.Flush);
}