#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  activitymsg ;
typedef  int XLogRecPtr ;
struct TYPE_10__ {int sentPtr; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ WalSnd ;
struct TYPE_12__ {int ws_file; } ;
struct TYPE_11__ {char* data; size_t len; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int GetCurrentTimestamp () ; 
 int GetFlushRecPtr () ; 
 int GetStandbyFlushRecPtr () ; 
 int /*<<< orphan*/  LagTrackerWrite (int,int) ; 
 int MAX_SEND_SIZE ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ ThisTimeLineID ; 
 int /*<<< orphan*/  WALSNDSTATE_STOPPING ; 
 int WalSndCaughtUp ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogRead (int /*<<< orphan*/ ,char*,int,int) ; 
 int am_cascading_walsender ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_2__*,int) ; 
 scalar_t__ got_STOPPING ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 TYPE_2__ output_message ; 
 int /*<<< orphan*/  pq_putmessage_noblock (char,char*,size_t) ; 
 int /*<<< orphan*/  pq_sendbyte (TYPE_2__*,char) ; 
 int /*<<< orphan*/  pq_sendint64 (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * readTimeLineHistory (scalar_t__) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  sendCxt ; 
 TYPE_3__* sendSeg ; 
 scalar_t__ sendTimeLine ; 
 int sendTimeLineIsHistoric ; 
 scalar_t__ sendTimeLineNextTLI ; 
 int sendTimeLineValidUpto ; 
 int sentPtr ; 
 int /*<<< orphan*/  set_ps_display (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int streamingDoneSending ; 
 int tliSwitchPoint (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_2__ tmpbuf ; 
 scalar_t__ update_process_title ; 

__attribute__((used)) static void
XLogSendPhysical(void)
{
	XLogRecPtr	SendRqstPtr;
	XLogRecPtr	startptr;
	XLogRecPtr	endptr;
	Size		nbytes;

	/* If requested switch the WAL sender to the stopping state. */
	if (got_STOPPING)
		WalSndSetState(WALSNDSTATE_STOPPING);

	if (streamingDoneSending)
	{
		WalSndCaughtUp = true;
		return;
	}

	/* Figure out how far we can safely send the WAL. */
	if (sendTimeLineIsHistoric)
	{
		/*
		 * Streaming an old timeline that's in this server's history, but is
		 * not the one we're currently inserting or replaying. It can be
		 * streamed up to the point where we switched off that timeline.
		 */
		SendRqstPtr = sendTimeLineValidUpto;
	}
	else if (am_cascading_walsender)
	{
		/*
		 * Streaming the latest timeline on a standby.
		 *
		 * Attempt to send all WAL that has already been replayed, so that we
		 * know it's valid. If we're receiving WAL through streaming
		 * replication, it's also OK to send any WAL that has been received
		 * but not replayed.
		 *
		 * The timeline we're recovering from can change, or we can be
		 * promoted. In either case, the current timeline becomes historic. We
		 * need to detect that so that we don't try to stream past the point
		 * where we switched to another timeline. We check for promotion or
		 * timeline switch after calculating FlushPtr, to avoid a race
		 * condition: if the timeline becomes historic just after we checked
		 * that it was still current, it's still be OK to stream it up to the
		 * FlushPtr that was calculated before it became historic.
		 */
		bool		becameHistoric = false;

		SendRqstPtr = GetStandbyFlushRecPtr();

		if (!RecoveryInProgress())
		{
			/*
			 * We have been promoted. RecoveryInProgress() updated
			 * ThisTimeLineID to the new current timeline.
			 */
			am_cascading_walsender = false;
			becameHistoric = true;
		}
		else
		{
			/*
			 * Still a cascading standby. But is the timeline we're sending
			 * still the one recovery is recovering from? ThisTimeLineID was
			 * updated by the GetStandbyFlushRecPtr() call above.
			 */
			if (sendTimeLine != ThisTimeLineID)
				becameHistoric = true;
		}

		if (becameHistoric)
		{
			/*
			 * The timeline we were sending has become historic. Read the
			 * timeline history file of the new timeline to see where exactly
			 * we forked off from the timeline we were sending.
			 */
			List	   *history;

			history = readTimeLineHistory(ThisTimeLineID);
			sendTimeLineValidUpto = tliSwitchPoint(sendTimeLine, history, &sendTimeLineNextTLI);

			Assert(sendTimeLine < sendTimeLineNextTLI);
			list_free_deep(history);

			sendTimeLineIsHistoric = true;

			SendRqstPtr = sendTimeLineValidUpto;
		}
	}
	else
	{
		/*
		 * Streaming the current timeline on a master.
		 *
		 * Attempt to send all data that's already been written out and
		 * fsync'd to disk.  We cannot go further than what's been written out
		 * given the current implementation of XLogRead().  And in any case
		 * it's unsafe to send WAL that is not securely down to disk on the
		 * master: if the master subsequently crashes and restarts, standbys
		 * must not have applied any WAL that got lost on the master.
		 */
		SendRqstPtr = GetFlushRecPtr();
	}

	/*
	 * Record the current system time as an approximation of the time at which
	 * this WAL location was written for the purposes of lag tracking.
	 *
	 * In theory we could make XLogFlush() record a time in shmem whenever WAL
	 * is flushed and we could get that time as well as the LSN when we call
	 * GetFlushRecPtr() above (and likewise for the cascading standby
	 * equivalent), but rather than putting any new code into the hot WAL path
	 * it seems good enough to capture the time here.  We should reach this
	 * after XLogFlush() runs WalSndWakeupProcessRequests(), and although that
	 * may take some time, we read the WAL flush pointer and take the time
	 * very close to together here so that we'll get a later position if it is
	 * still moving.
	 *
	 * Because LagTrackerWrite ignores samples when the LSN hasn't advanced,
	 * this gives us a cheap approximation for the WAL flush time for this
	 * LSN.
	 *
	 * Note that the LSN is not necessarily the LSN for the data contained in
	 * the present message; it's the end of the WAL, which might be further
	 * ahead.  All the lag tracking machinery cares about is finding out when
	 * that arbitrary LSN is eventually reported as written, flushed and
	 * applied, so that it can measure the elapsed time.
	 */
	LagTrackerWrite(SendRqstPtr, GetCurrentTimestamp());

	/*
	 * If this is a historic timeline and we've reached the point where we
	 * forked to the next timeline, stop streaming.
	 *
	 * Note: We might already have sent WAL > sendTimeLineValidUpto. The
	 * startup process will normally replay all WAL that has been received
	 * from the master, before promoting, but if the WAL streaming is
	 * terminated at a WAL page boundary, the valid portion of the timeline
	 * might end in the middle of a WAL record. We might've already sent the
	 * first half of that partial WAL record to the cascading standby, so that
	 * sentPtr > sendTimeLineValidUpto. That's OK; the cascading standby can't
	 * replay the partial WAL record either, so it can still follow our
	 * timeline switch.
	 */
	if (sendTimeLineIsHistoric && sendTimeLineValidUpto <= sentPtr)
	{
		/* close the current file. */
		if (sendSeg->ws_file >= 0)
			close(sendSeg->ws_file);
		sendSeg->ws_file = -1;

		/* Send CopyDone */
		pq_putmessage_noblock('c', NULL, 0);
		streamingDoneSending = true;

		WalSndCaughtUp = true;

		elog(DEBUG1, "walsender reached end of timeline at %X/%X (sent up to %X/%X)",
			 (uint32) (sendTimeLineValidUpto >> 32), (uint32) sendTimeLineValidUpto,
			 (uint32) (sentPtr >> 32), (uint32) sentPtr);
		return;
	}

	/* Do we have any work to do? */
	Assert(sentPtr <= SendRqstPtr);
	if (SendRqstPtr <= sentPtr)
	{
		WalSndCaughtUp = true;
		return;
	}

	/*
	 * Figure out how much to send in one message. If there's no more than
	 * MAX_SEND_SIZE bytes to send, send everything. Otherwise send
	 * MAX_SEND_SIZE bytes, but round back to logfile or page boundary.
	 *
	 * The rounding is not only for performance reasons. Walreceiver relies on
	 * the fact that we never split a WAL record across two messages. Since a
	 * long WAL record is split at page boundary into continuation records,
	 * page boundary is always a safe cut-off point. We also assume that
	 * SendRqstPtr never points to the middle of a WAL record.
	 */
	startptr = sentPtr;
	endptr = startptr;
	endptr += MAX_SEND_SIZE;

	/* if we went beyond SendRqstPtr, back off */
	if (SendRqstPtr <= endptr)
	{
		endptr = SendRqstPtr;
		if (sendTimeLineIsHistoric)
			WalSndCaughtUp = false;
		else
			WalSndCaughtUp = true;
	}
	else
	{
		/* round down to page boundary. */
		endptr -= (endptr % XLOG_BLCKSZ);
		WalSndCaughtUp = false;
	}

	nbytes = endptr - startptr;
	Assert(nbytes <= MAX_SEND_SIZE);

	/*
	 * OK to read and send the slice.
	 */
	resetStringInfo(&output_message);
	pq_sendbyte(&output_message, 'w');

	pq_sendint64(&output_message, startptr);	/* dataStart */
	pq_sendint64(&output_message, SendRqstPtr); /* walEnd */
	pq_sendint64(&output_message, 0);	/* sendtime, filled in last */

	/*
	 * Read the log directly into the output buffer to avoid extra memcpy
	 * calls.
	 */
	enlargeStringInfo(&output_message, nbytes);
	XLogRead(sendCxt, &output_message.data[output_message.len], startptr, nbytes);
	output_message.len += nbytes;
	output_message.data[output_message.len] = '\0';

	/*
	 * Fill the send timestamp last, so that it is taken as late as possible.
	 */
	resetStringInfo(&tmpbuf);
	pq_sendint64(&tmpbuf, GetCurrentTimestamp());
	memcpy(&output_message.data[1 + sizeof(int64) + sizeof(int64)],
		   tmpbuf.data, sizeof(int64));

	pq_putmessage_noblock('d', output_message.data, output_message.len);

	sentPtr = endptr;

	/* Update shared memory status */
	{
		WalSnd	   *walsnd = MyWalSnd;

		SpinLockAcquire(&walsnd->mutex);
		walsnd->sentPtr = sentPtr;
		SpinLockRelease(&walsnd->mutex);
	}

	/* Report progress of XLOG streaming in PS display */
	if (update_process_title)
	{
		char		activitymsg[50];

		snprintf(activitymsg, sizeof(activitymsg), "streaming %X/%X",
				 (uint32) (sentPtr >> 32), (uint32) sentPtr);
		set_ps_display(activitymsg, false);
	}

	return;
}