#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int XLogRecPtr ;
struct TYPE_3__ {int write; int flush; int apply; int writeLag; int flushLag; int applyLag; int /*<<< orphan*/  mutex; void* replyTime; } ;
typedef  TYPE_1__ WalSnd ;
typedef  void* TimestampTz ;
typedef  int TimeOffset ;

/* Variables and functions */
 scalar_t__ DEBUG2 ; 
 void* GetCurrentTimestamp () ; 
 int InvalidXLogRecPtr ; 
 int LagTrackerRead (int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  LogicalConfirmReceivedLocation (int) ; 
 scalar_t__ MyReplicationSlot ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  PhysicalConfirmReceivedLocation (int) ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_APPLY ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_FLUSH ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_WRITE ; 
 scalar_t__ SlotIsLogical (scalar_t__) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SyncRepReleaseWaiters () ; 
 int /*<<< orphan*/  WalSndKeepalive (int) ; 
 int /*<<< orphan*/  am_cascading_walsender ; 
 int /*<<< orphan*/  elog (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ log_min_messages ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pq_getmsgbyte (int /*<<< orphan*/ *) ; 
 void* pq_getmsgint64 (int /*<<< orphan*/ *) ; 
 char* pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_message ; 
 int sentPtr ; 
 int /*<<< orphan*/  timestamptz_to_str (void*) ; 

__attribute__((used)) static void
ProcessStandbyReplyMessage(void)
{
	XLogRecPtr	writePtr,
				flushPtr,
				applyPtr;
	bool		replyRequested;
	TimeOffset	writeLag,
				flushLag,
				applyLag;
	bool		clearLagTimes;
	TimestampTz now;
	TimestampTz replyTime;

	static bool fullyAppliedLastTime = false;

	/* the caller already consumed the msgtype byte */
	writePtr = pq_getmsgint64(&reply_message);
	flushPtr = pq_getmsgint64(&reply_message);
	applyPtr = pq_getmsgint64(&reply_message);
	replyTime = pq_getmsgint64(&reply_message);
	replyRequested = pq_getmsgbyte(&reply_message);

	if (log_min_messages <= DEBUG2)
	{
		char	   *replyTimeStr;

		/* Copy because timestamptz_to_str returns a static buffer */
		replyTimeStr = pstrdup(timestamptz_to_str(replyTime));

		elog(DEBUG2, "write %X/%X flush %X/%X apply %X/%X%s reply_time %s",
			 (uint32) (writePtr >> 32), (uint32) writePtr,
			 (uint32) (flushPtr >> 32), (uint32) flushPtr,
			 (uint32) (applyPtr >> 32), (uint32) applyPtr,
			 replyRequested ? " (reply requested)" : "",
			 replyTimeStr);

		pfree(replyTimeStr);
	}

	/* See if we can compute the round-trip lag for these positions. */
	now = GetCurrentTimestamp();
	writeLag = LagTrackerRead(SYNC_REP_WAIT_WRITE, writePtr, now);
	flushLag = LagTrackerRead(SYNC_REP_WAIT_FLUSH, flushPtr, now);
	applyLag = LagTrackerRead(SYNC_REP_WAIT_APPLY, applyPtr, now);

	/*
	 * If the standby reports that it has fully replayed the WAL in two
	 * consecutive reply messages, then the second such message must result
	 * from wal_receiver_status_interval expiring on the standby.  This is a
	 * convenient time to forget the lag times measured when it last
	 * wrote/flushed/applied a WAL record, to avoid displaying stale lag data
	 * until more WAL traffic arrives.
	 */
	clearLagTimes = false;
	if (applyPtr == sentPtr)
	{
		if (fullyAppliedLastTime)
			clearLagTimes = true;
		fullyAppliedLastTime = true;
	}
	else
		fullyAppliedLastTime = false;

	/* Send a reply if the standby requested one. */
	if (replyRequested)
		WalSndKeepalive(false);

	/*
	 * Update shared state for this WalSender process based on reply data from
	 * standby.
	 */
	{
		WalSnd	   *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->write = writePtr;
		walsnd->flush = flushPtr;
		walsnd->apply = applyPtr;
		if (writeLag != -1 || clearLagTimes)
			walsnd->writeLag = writeLag;
		if (flushLag != -1 || clearLagTimes)
			walsnd->flushLag = flushLag;
		if (applyLag != -1 || clearLagTimes)
			walsnd->applyLag = applyLag;
		walsnd->replyTime = replyTime;
		SpinLockRelease(&walsnd->mutex);
	}

	if (!am_cascading_walsender)
		SyncRepReleaseWaiters();

	/*
	 * Advance our local xmin horizon when the client confirmed a flush.
	 */
	if (MyReplicationSlot && flushPtr != InvalidXLogRecPtr)
	{
		if (SlotIsLogical(MyReplicationSlot))
			LogicalConfirmReceivedLocation(flushPtr);
		else
			PhysicalConfirmReceivedLocation(flushPtr);
	}
}