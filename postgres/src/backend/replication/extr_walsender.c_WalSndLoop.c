#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* WalSndSendDataCallback ) () ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int ConfigReloadPending ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_2__* MyProcPort ; 
 TYPE_1__* MyWalSnd ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessRepliesIfAny () ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SyncRepInitConfig () ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_SENDER_MAIN ; 
 scalar_t__ WALSNDSTATE_CATCHUP ; 
 int /*<<< orphan*/  WALSNDSTATE_STREAMING ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatchOrSocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int WalSndCaughtUp ; 
 int /*<<< orphan*/  WalSndCheckTimeOut () ; 
 long WalSndComputeSleeptime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndDone (int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  WalSndKeepaliveIfNecessary () ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndShutdown () ; 
 int /*<<< orphan*/  application_name ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ got_SIGUSR2 ; 
 int /*<<< orphan*/  last_reply_timestamp ; 
 scalar_t__ pq_flush_if_writable () ; 
 scalar_t__ pq_is_send_pending () ; 
 scalar_t__ streamingDoneReceiving ; 
 scalar_t__ streamingDoneSending ; 
 int waiting_for_ping_response ; 

__attribute__((used)) static void
WalSndLoop(WalSndSendDataCallback send_data)
{
	/*
	 * Initialize the last reply timestamp. That enables timeout processing
	 * from hereon.
	 */
	last_reply_timestamp = GetCurrentTimestamp();
	waiting_for_ping_response = false;

	/*
	 * Loop until we reach the end of this timeline or the client requests to
	 * stop streaming.
	 */
	for (;;)
	{
		/* Clear any already-pending wakeups */
		ResetLatch(MyLatch);

		CHECK_FOR_INTERRUPTS();

		/* Process any requests or signals received recently */
		if (ConfigReloadPending)
		{
			ConfigReloadPending = false;
			ProcessConfigFile(PGC_SIGHUP);
			SyncRepInitConfig();
		}

		/* Check for input from the client */
		ProcessRepliesIfAny();

		/*
		 * If we have received CopyDone from the client, sent CopyDone
		 * ourselves, and the output buffer is empty, it's time to exit
		 * streaming.
		 */
		if (streamingDoneReceiving && streamingDoneSending &&
			!pq_is_send_pending())
			break;

		/*
		 * If we don't have any pending data in the output buffer, try to send
		 * some more.  If there is some, we don't bother to call send_data
		 * again until we've flushed it ... but we'd better assume we are not
		 * caught up.
		 */
		if (!pq_is_send_pending())
			send_data();
		else
			WalSndCaughtUp = false;

		/* Try to flush pending output to the client */
		if (pq_flush_if_writable() != 0)
			WalSndShutdown();

		/* If nothing remains to be sent right now ... */
		if (WalSndCaughtUp && !pq_is_send_pending())
		{
			/*
			 * If we're in catchup state, move to streaming.  This is an
			 * important state change for users to know about, since before
			 * this point data loss might occur if the primary dies and we
			 * need to failover to the standby. The state change is also
			 * important for synchronous replication, since commits that
			 * started to wait at that point might wait for some time.
			 */
			if (MyWalSnd->state == WALSNDSTATE_CATCHUP)
			{
				ereport(DEBUG1,
						(errmsg("\"%s\" has now caught up with upstream server",
								application_name)));
				WalSndSetState(WALSNDSTATE_STREAMING);
			}

			/*
			 * When SIGUSR2 arrives, we send any outstanding logs up to the
			 * shutdown checkpoint record (i.e., the latest record), wait for
			 * them to be replicated to the standby, and exit. This may be a
			 * normal termination at shutdown, or a promotion, the walsender
			 * is not sure which.
			 */
			if (got_SIGUSR2)
				WalSndDone(send_data);
		}

		/* Check for replication timeout. */
		WalSndCheckTimeOut();

		/* Send keepalive if the time has come */
		WalSndKeepaliveIfNecessary();

		/*
		 * We don't block if not caught up, unless there is unsent data
		 * pending in which case we'd better block until the socket is
		 * write-ready.  This test is only needed for the case where the
		 * send_data callback handled a subset of the available data but then
		 * pq_flush_if_writable flushed it all --- we should immediately try
		 * to send more.
		 */
		if ((WalSndCaughtUp && !streamingDoneSending) || pq_is_send_pending())
		{
			long		sleeptime;
			int			wakeEvents;

			wakeEvents = WL_LATCH_SET | WL_EXIT_ON_PM_DEATH | WL_TIMEOUT |
				WL_SOCKET_READABLE;

			/*
			 * Use fresh timestamp, not last_processing, to reduce the chance
			 * of reaching wal_sender_timeout before sending a keepalive.
			 */
			sleeptime = WalSndComputeSleeptime(GetCurrentTimestamp());

			if (pq_is_send_pending())
				wakeEvents |= WL_SOCKET_WRITEABLE;

			/* Sleep until something happens or we time out */
			(void) WaitLatchOrSocket(MyLatch, wakeEvents,
									 MyProcPort->sock, sleeptime,
									 WAIT_EVENT_WAL_SENDER_MAIN);
		}
	}
	return;
}