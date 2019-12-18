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
struct TYPE_6__ {int /*<<< orphan*/  restart_lsn; int /*<<< orphan*/  confirmed_flush; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  sentPtr; } ;
struct TYPE_7__ {int /*<<< orphan*/  options; int /*<<< orphan*/  startpoint; int /*<<< orphan*/  slotname; } ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  TYPE_2__ StartReplicationCmd ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CheckLogicalDecodingRequirements () ; 
 int /*<<< orphan*/  CreateDecodingContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  EndCommand (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeDecodingContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 TYPE_5__* MyReplicationSlot ; 
 TYPE_4__* MyWalSnd ; 
 int /*<<< orphan*/  RecoveryInProgress () ; 
 int /*<<< orphan*/  ReplicationSlotAcquire (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReplicationSlotRelease () ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SyncRepInitConfig () ; 
 int /*<<< orphan*/  WALSNDSTATE_CATCHUP ; 
 int /*<<< orphan*/  WALSNDSTATE_STARTUP ; 
 int /*<<< orphan*/  WalSndLoop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndPrepareWrite ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndUpdateProgress ; 
 int /*<<< orphan*/  WalSndWriteData ; 
 int /*<<< orphan*/  XLogSendLogical ; 
 scalar_t__ am_cascading_walsender ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int got_STOPPING ; 
 int /*<<< orphan*/  logical_decoding_ctx ; 
 int /*<<< orphan*/  logical_read_xlog_page ; 
 int /*<<< orphan*/  logical_startptr ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_flush () ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int replication_active ; 
 int /*<<< orphan*/  sentPtr ; 

__attribute__((used)) static void
StartLogicalReplication(StartReplicationCmd *cmd)
{
	StringInfoData buf;

	/* make sure that our requirements are still fulfilled */
	CheckLogicalDecodingRequirements();

	Assert(!MyReplicationSlot);

	ReplicationSlotAcquire(cmd->slotname, true);

	/*
	 * Force a disconnect, so that the decoding code doesn't need to care
	 * about an eventual switch from running in recovery, to running in a
	 * normal environment. Client code is expected to handle reconnects.
	 */
	if (am_cascading_walsender && !RecoveryInProgress())
	{
		ereport(LOG,
				(errmsg("terminating walsender process after promotion")));
		got_STOPPING = true;
	}

	/*
	 * Create our decoding context, making it start at the previously ack'ed
	 * position.
	 *
	 * Do this before sending a CopyBothResponse message, so that any errors
	 * are reported early.
	 */
	logical_decoding_ctx =
		CreateDecodingContext(cmd->startpoint, cmd->options, false,
							  logical_read_xlog_page,
							  WalSndPrepareWrite, WalSndWriteData,
							  WalSndUpdateProgress);


	WalSndSetState(WALSNDSTATE_CATCHUP);

	/* Send a CopyBothResponse message, and start streaming */
	pq_beginmessage(&buf, 'W');
	pq_sendbyte(&buf, 0);
	pq_sendint16(&buf, 0);
	pq_endmessage(&buf);
	pq_flush();


	/* Start reading WAL from the oldest required WAL. */
	logical_startptr = MyReplicationSlot->data.restart_lsn;

	/*
	 * Report the location after which we'll send out further commits as the
	 * current sentPtr.
	 */
	sentPtr = MyReplicationSlot->data.confirmed_flush;

	/* Also update the sent position status in shared memory */
	SpinLockAcquire(&MyWalSnd->mutex);
	MyWalSnd->sentPtr = MyReplicationSlot->data.restart_lsn;
	SpinLockRelease(&MyWalSnd->mutex);

	replication_active = true;

	SyncRepInitConfig();

	/* Main loop of walsender */
	WalSndLoop(XLogSendLogical);

	FreeDecodingContext(logical_decoding_ctx);
	ReplicationSlotRelease();

	replication_active = false;
	if (got_STOPPING)
		proc_exit(0);
	WalSndSetState(WALSNDSTATE_STARTUP);

	/* Get out of COPY mode (CommandComplete). */
	EndCommand("COPY 0", DestRemote);
}