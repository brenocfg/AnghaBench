#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;
typedef  scalar_t__ TimestampTz ;
struct TYPE_11__ {int /*<<< orphan*/  sock; } ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__* out; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ LogicalDecodingContext ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int ConfigReloadPending ; 
 scalar_t__ GetCurrentTimestamp () ; 
 int /*<<< orphan*/  MyLatch ; 
 TYPE_7__* MyProcPort ; 
 int /*<<< orphan*/  PGC_SIGHUP ; 
 int /*<<< orphan*/  ProcessConfigFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcessRepliesIfAny () ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SyncRepInitConfig () ; 
 scalar_t__ TimestampTzPlusMilliseconds (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WAIT_EVENT_WAL_SENDER_WRITE_DATA ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_LATCH_SET ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatchOrSocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndCheckTimeOut () ; 
 long WalSndComputeSleeptime (scalar_t__) ; 
 int /*<<< orphan*/  WalSndKeepaliveIfNecessary () ; 
 int /*<<< orphan*/  WalSndShutdown () ; 
 int /*<<< orphan*/  last_reply_timestamp ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pq_flush_if_writable () ; 
 int /*<<< orphan*/  pq_is_send_pending () ; 
 int /*<<< orphan*/  pq_putmessage_noblock (char,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint64 (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  resetStringInfo (TYPE_3__*) ; 
 TYPE_3__ tmpbuf ; 
 int wal_sender_timeout ; 

__attribute__((used)) static void
WalSndWriteData(LogicalDecodingContext *ctx, XLogRecPtr lsn, TransactionId xid,
				bool last_write)
{
	TimestampTz now;

	/*
	 * Fill the send timestamp last, so that it is taken as late as possible.
	 * This is somewhat ugly, but the protocol is set as it's already used for
	 * several releases by streaming physical replication.
	 */
	resetStringInfo(&tmpbuf);
	now = GetCurrentTimestamp();
	pq_sendint64(&tmpbuf, now);
	memcpy(&ctx->out->data[1 + sizeof(int64) + sizeof(int64)],
		   tmpbuf.data, sizeof(int64));

	/* output previously gathered data in a CopyData packet */
	pq_putmessage_noblock('d', ctx->out->data, ctx->out->len);

	CHECK_FOR_INTERRUPTS();

	/* Try to flush pending output to the client */
	if (pq_flush_if_writable() != 0)
		WalSndShutdown();

	/* Try taking fast path unless we get too close to walsender timeout. */
	if (now < TimestampTzPlusMilliseconds(last_reply_timestamp,
										  wal_sender_timeout / 2) &&
		!pq_is_send_pending())
	{
		return;
	}

	/* If we have pending write here, go to slow path */
	for (;;)
	{
		int			wakeEvents;
		long		sleeptime;

		/* Check for input from the client */
		ProcessRepliesIfAny();

		/* die if timeout was reached */
		WalSndCheckTimeOut();

		/* Send keepalive if the time has come */
		WalSndKeepaliveIfNecessary();

		if (!pq_is_send_pending())
			break;

		sleeptime = WalSndComputeSleeptime(GetCurrentTimestamp());

		wakeEvents = WL_LATCH_SET | WL_EXIT_ON_PM_DEATH |
			WL_SOCKET_WRITEABLE | WL_SOCKET_READABLE | WL_TIMEOUT;

		/* Sleep until something happens or we time out */
		(void) WaitLatchOrSocket(MyLatch, wakeEvents,
								 MyProcPort->sock, sleeptime,
								 WAIT_EVENT_WAL_SENDER_WRITE_DATA);

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

		/* Try to flush pending output to the client */
		if (pq_flush_if_writable() != 0)
			WalSndShutdown();
	}

	/* reactivate latch so WalSndLoop knows to continue */
	SetLatch(MyLatch);
}