#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
typedef  void* TimestampTz ;
typedef  int /*<<< orphan*/  TimeLineID ;
struct TYPE_4__ {int /*<<< orphan*/  ThisTimeLineID; } ;
struct TYPE_6__ {TYPE_1__ checkPointCopy; } ;
struct TYPE_5__ {int /*<<< orphan*/  recoveryWakeupLatch; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckForStandbyTrigger () ; 
 TYPE_3__* ControlFile ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  ERROR ; 
 void* GetCurrentTimestamp () ; 
 int GetWalRcvWriteRecPtr (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HandleStartupProcInterrupts () ; 
 scalar_t__ InArchiveRecovery ; 
 int /*<<< orphan*/  PANIC ; 
 int /*<<< orphan*/  PrimaryConnInfo ; 
 int /*<<< orphan*/  PrimarySlotName ; 
 int /*<<< orphan*/  RECOVERY_TARGET_TIMELINE_LATEST ; 
 int RedoStartLSN ; 
 int /*<<< orphan*/  RequestXLogStreaming (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCurrentChunkStartTime (void*) ; 
 int /*<<< orphan*/  ShutdownWalRcv () ; 
 int StandbyMode ; 
 int /*<<< orphan*/  TimestampDifference (void*,void*,long*,int*) ; 
 int /*<<< orphan*/  TimestampDifferenceExceeds (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAIT_EVENT_RECOVERY_WAL_ALL ; 
 int /*<<< orphan*/  WAIT_EVENT_RECOVERY_WAL_STREAM ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatch (int /*<<< orphan*/ *,int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalRcvForceReply () ; 
 int /*<<< orphan*/  WalRcvStreaming () ; 
 int XLOG_FROM_ANY ; 
#define  XLOG_FROM_ARCHIVE 130 
#define  XLOG_FROM_PG_WAL 129 
#define  XLOG_FROM_STREAM 128 
 TYPE_2__* XLogCtl ; 
 int XLogFileRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int) ; 
 int XLogFileReadAnyTLI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XLogReceiptSource ; 
 void* XLogReceiptTime ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  curFileTLI ; 
 int currentSource ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  expectedTLEs ; 
 int lastSourceFailed ; 
 int readFile ; 
 int /*<<< orphan*/  readSegNo ; 
 int readSource ; 
 int /*<<< orphan*/  readTimeLineHistory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receiveTLI ; 
 int receivedUpto ; 
 int /*<<< orphan*/  recoveryTargetTimeLineGoal ; 
 int /*<<< orphan*/  rescanLatestTimeLine () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tliOfPointInHistory (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wal_retrieve_retry_interval ; 
 int /*<<< orphan*/ * xlogSourceNames ; 

__attribute__((used)) static bool
WaitForWALToBecomeAvailable(XLogRecPtr RecPtr, bool randAccess,
							bool fetching_ckpt, XLogRecPtr tliRecPtr)
{
	static TimestampTz last_fail_time = 0;
	TimestampTz now;
	bool		streaming_reply_sent = false;

	/*-------
	 * Standby mode is implemented by a state machine:
	 *
	 * 1. Read from either archive or pg_wal (XLOG_FROM_ARCHIVE), or just
	 *	  pg_wal (XLOG_FROM_PG_WAL)
	 * 2. Check trigger file
	 * 3. Read from primary server via walreceiver (XLOG_FROM_STREAM)
	 * 4. Rescan timelines
	 * 5. Sleep wal_retrieve_retry_interval milliseconds, and loop back to 1.
	 *
	 * Failure to read from the current source advances the state machine to
	 * the next state.
	 *
	 * 'currentSource' indicates the current state. There are no currentSource
	 * values for "check trigger", "rescan timelines", and "sleep" states,
	 * those actions are taken when reading from the previous source fails, as
	 * part of advancing to the next state.
	 *-------
	 */
	if (!InArchiveRecovery)
		currentSource = XLOG_FROM_PG_WAL;
	else if (currentSource == 0)
		currentSource = XLOG_FROM_ARCHIVE;

	for (;;)
	{
		int			oldSource = currentSource;

		/*
		 * First check if we failed to read from the current source, and
		 * advance the state machine if so. The failure to read might've
		 * happened outside this function, e.g when a CRC check fails on a
		 * record, or within this loop.
		 */
		if (lastSourceFailed)
		{
			switch (currentSource)
			{
				case XLOG_FROM_ARCHIVE:
				case XLOG_FROM_PG_WAL:

					/*
					 * Check to see if the trigger file exists. Note that we
					 * do this only after failure, so when you create the
					 * trigger file, we still finish replaying as much as we
					 * can from archive and pg_wal before failover.
					 */
					if (StandbyMode && CheckForStandbyTrigger())
					{
						ShutdownWalRcv();
						return false;
					}

					/*
					 * Not in standby mode, and we've now tried the archive
					 * and pg_wal.
					 */
					if (!StandbyMode)
						return false;

					/*
					 * If primary_conninfo is set, launch walreceiver to try
					 * to stream the missing WAL.
					 *
					 * If fetching_ckpt is true, RecPtr points to the initial
					 * checkpoint location. In that case, we use RedoStartLSN
					 * as the streaming start position instead of RecPtr, so
					 * that when we later jump backwards to start redo at
					 * RedoStartLSN, we will have the logs streamed already.
					 */
					if (PrimaryConnInfo && strcmp(PrimaryConnInfo, "") != 0)
					{
						XLogRecPtr	ptr;
						TimeLineID	tli;

						if (fetching_ckpt)
						{
							ptr = RedoStartLSN;
							tli = ControlFile->checkPointCopy.ThisTimeLineID;
						}
						else
						{
							ptr = RecPtr;

							/*
							 * Use the record begin position to determine the
							 * TLI, rather than the position we're reading.
							 */
							tli = tliOfPointInHistory(tliRecPtr, expectedTLEs);

							if (curFileTLI > 0 && tli < curFileTLI)
								elog(ERROR, "according to history file, WAL location %X/%X belongs to timeline %u, but previous recovered WAL file came from timeline %u",
									 (uint32) (tliRecPtr >> 32),
									 (uint32) tliRecPtr,
									 tli, curFileTLI);
						}
						curFileTLI = tli;
						RequestXLogStreaming(tli, ptr, PrimaryConnInfo,
											 PrimarySlotName);
						receivedUpto = 0;
					}

					/*
					 * Move to XLOG_FROM_STREAM state in either case. We'll
					 * get immediate failure if we didn't launch walreceiver,
					 * and move on to the next state.
					 */
					currentSource = XLOG_FROM_STREAM;
					break;

				case XLOG_FROM_STREAM:

					/*
					 * Failure while streaming. Most likely, we got here
					 * because streaming replication was terminated, or
					 * promotion was triggered. But we also get here if we
					 * find an invalid record in the WAL streamed from master,
					 * in which case something is seriously wrong. There's
					 * little chance that the problem will just go away, but
					 * PANIC is not good for availability either, especially
					 * in hot standby mode. So, we treat that the same as
					 * disconnection, and retry from archive/pg_wal again. The
					 * WAL in the archive should be identical to what was
					 * streamed, so it's unlikely that it helps, but one can
					 * hope...
					 */

					/*
					 * We should be able to move to XLOG_FROM_STREAM
					 * only in standby mode.
					 */
					Assert(StandbyMode);

					/*
					 * Before we leave XLOG_FROM_STREAM state, make sure that
					 * walreceiver is not active, so that it won't overwrite
					 * WAL that we restore from archive.
					 */
					if (WalRcvStreaming())
						ShutdownWalRcv();

					/*
					 * Before we sleep, re-scan for possible new timelines if
					 * we were requested to recover to the latest timeline.
					 */
					if (recoveryTargetTimeLineGoal == RECOVERY_TARGET_TIMELINE_LATEST)
					{
						if (rescanLatestTimeLine())
						{
							currentSource = XLOG_FROM_ARCHIVE;
							break;
						}
					}

					/*
					 * XLOG_FROM_STREAM is the last state in our state
					 * machine, so we've exhausted all the options for
					 * obtaining the requested WAL. We're going to loop back
					 * and retry from the archive, but if it hasn't been long
					 * since last attempt, sleep wal_retrieve_retry_interval
					 * milliseconds to avoid busy-waiting.
					 */
					now = GetCurrentTimestamp();
					if (!TimestampDifferenceExceeds(last_fail_time, now,
													wal_retrieve_retry_interval))
					{
						long		secs,
									wait_time;
						int			usecs;

						TimestampDifference(last_fail_time, now, &secs, &usecs);
						wait_time = wal_retrieve_retry_interval -
							(secs * 1000 + usecs / 1000);

						(void) WaitLatch(&XLogCtl->recoveryWakeupLatch,
										 WL_LATCH_SET | WL_TIMEOUT |
										 WL_EXIT_ON_PM_DEATH,
										 wait_time,
										 WAIT_EVENT_RECOVERY_WAL_STREAM);
						ResetLatch(&XLogCtl->recoveryWakeupLatch);
						now = GetCurrentTimestamp();
					}
					last_fail_time = now;
					currentSource = XLOG_FROM_ARCHIVE;
					break;

				default:
					elog(ERROR, "unexpected WAL source %d", currentSource);
			}
		}
		else if (currentSource == XLOG_FROM_PG_WAL)
		{
			/*
			 * We just successfully read a file in pg_wal. We prefer files in
			 * the archive over ones in pg_wal, so try the next file again
			 * from the archive first.
			 */
			if (InArchiveRecovery)
				currentSource = XLOG_FROM_ARCHIVE;
		}

		if (currentSource != oldSource)
			elog(DEBUG2, "switched WAL source from %s to %s after %s",
				 xlogSourceNames[oldSource], xlogSourceNames[currentSource],
				 lastSourceFailed ? "failure" : "success");

		/*
		 * We've now handled possible failure. Try to read from the chosen
		 * source.
		 */
		lastSourceFailed = false;

		switch (currentSource)
		{
			case XLOG_FROM_ARCHIVE:
			case XLOG_FROM_PG_WAL:
				/* Close any old file we might have open. */
				if (readFile >= 0)
				{
					close(readFile);
					readFile = -1;
				}
				/* Reset curFileTLI if random fetch. */
				if (randAccess)
					curFileTLI = 0;

				/*
				 * Try to restore the file from archive, or read an existing
				 * file from pg_wal.
				 */
				readFile = XLogFileReadAnyTLI(readSegNo, DEBUG2,
											  currentSource == XLOG_FROM_ARCHIVE ? XLOG_FROM_ANY :
											  currentSource);
				if (readFile >= 0)
					return true;	/* success! */

				/*
				 * Nope, not found in archive or pg_wal.
				 */
				lastSourceFailed = true;
				break;

			case XLOG_FROM_STREAM:
				{
					bool		havedata;

					/*
					 * We should be able to move to XLOG_FROM_STREAM
					 * only in standby mode.
					 */
					Assert(StandbyMode);

					/*
					 * Check if WAL receiver is still active.
					 */
					if (!WalRcvStreaming())
					{
						lastSourceFailed = true;
						break;
					}

					/*
					 * Walreceiver is active, so see if new data has arrived.
					 *
					 * We only advance XLogReceiptTime when we obtain fresh
					 * WAL from walreceiver and observe that we had already
					 * processed everything before the most recent "chunk"
					 * that it flushed to disk.  In steady state where we are
					 * keeping up with the incoming data, XLogReceiptTime will
					 * be updated on each cycle. When we are behind,
					 * XLogReceiptTime will not advance, so the grace time
					 * allotted to conflicting queries will decrease.
					 */
					if (RecPtr < receivedUpto)
						havedata = true;
					else
					{
						XLogRecPtr	latestChunkStart;

						receivedUpto = GetWalRcvWriteRecPtr(&latestChunkStart, &receiveTLI);
						if (RecPtr < receivedUpto && receiveTLI == curFileTLI)
						{
							havedata = true;
							if (latestChunkStart <= RecPtr)
							{
								XLogReceiptTime = GetCurrentTimestamp();
								SetCurrentChunkStartTime(XLogReceiptTime);
							}
						}
						else
							havedata = false;
					}
					if (havedata)
					{
						/*
						 * Great, streamed far enough.  Open the file if it's
						 * not open already.  Also read the timeline history
						 * file if we haven't initialized timeline history
						 * yet; it should be streamed over and present in
						 * pg_wal by now.  Use XLOG_FROM_STREAM so that source
						 * info is set correctly and XLogReceiptTime isn't
						 * changed.
						 */
						if (readFile < 0)
						{
							if (!expectedTLEs)
								expectedTLEs = readTimeLineHistory(receiveTLI);
							readFile = XLogFileRead(readSegNo, PANIC,
													receiveTLI,
													XLOG_FROM_STREAM, false);
							Assert(readFile >= 0);
						}
						else
						{
							/* just make sure source info is correct... */
							readSource = XLOG_FROM_STREAM;
							XLogReceiptSource = XLOG_FROM_STREAM;
							return true;
						}
						break;
					}

					/*
					 * Data not here yet. Check for trigger, then wait for
					 * walreceiver to wake us up when new WAL arrives.
					 */
					if (CheckForStandbyTrigger())
					{
						/*
						 * Note that we don't "return false" immediately here.
						 * After being triggered, we still want to replay all
						 * the WAL that was already streamed. It's in pg_wal
						 * now, so we just treat this as a failure, and the
						 * state machine will move on to replay the streamed
						 * WAL from pg_wal, and then recheck the trigger and
						 * exit replay.
						 */
						lastSourceFailed = true;
						break;
					}

					/*
					 * Since we have replayed everything we have received so
					 * far and are about to start waiting for more WAL, let's
					 * tell the upstream server our replay location now so
					 * that pg_stat_replication doesn't show stale
					 * information.
					 */
					if (!streaming_reply_sent)
					{
						WalRcvForceReply();
						streaming_reply_sent = true;
					}

					/*
					 * Wait for more WAL to arrive. Time out after 5 seconds
					 * to react to a trigger file promptly and to check if the
					 * WAL receiver is still active.
					 */
					(void) WaitLatch(&XLogCtl->recoveryWakeupLatch,
									 WL_LATCH_SET | WL_TIMEOUT |
									 WL_EXIT_ON_PM_DEATH,
									 5000L, WAIT_EVENT_RECOVERY_WAL_ALL);
					ResetLatch(&XLogCtl->recoveryWakeupLatch);
					break;
				}

			default:
				elog(ERROR, "unexpected WAL source %d", currentSource);
		}

		/*
		 * This possibly-long loop needs to handle interrupts of startup
		 * process.
		 */
		HandleStartupProcInterrupts();
	}

	return false;				/* not reached */
}