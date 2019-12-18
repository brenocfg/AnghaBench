#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  startpos_str ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int XLogRecPtr ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TupOutputState ;
struct TYPE_5__ {int sentPtr; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {scalar_t__ timeline; int startpoint; scalar_t__ slotname; } ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  TYPE_1__ StartReplicationCmd ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/ * CreateDestReceiver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  DestRemoteSimple ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int GetFlushRecPtr () ; 
 int GetStandbyFlushRecPtr () ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int InvalidXLogRecPtr ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int /*<<< orphan*/  MyReplicationSlot ; 
 TYPE_3__* MyWalSnd ; 
 int /*<<< orphan*/  ReplicationSlotAcquire (scalar_t__,int) ; 
 int /*<<< orphan*/  ReplicationSlotRelease () ; 
 scalar_t__ SlotIsLogical (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SyncRepInitConfig () ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 scalar_t__ ThisTimeLineID ; 
 int /*<<< orphan*/  TupleDescInitBuiltinEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WALSNDSTATE_CATCHUP ; 
 int /*<<< orphan*/  WALSNDSTATE_STARTUP ; 
 int /*<<< orphan*/  WalSndLoop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndSetState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRecPtrIsInvalid (int) ; 
 int /*<<< orphan*/  XLogSendPhysical ; 
 scalar_t__ am_cascading_walsender ; 
 int /*<<< orphan*/ * begin_tup_output_tupdesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tup_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  end_tup_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ got_STOPPING ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_flush () ; 
 int /*<<< orphan*/  pq_puttextmessage (char,char*) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * readTimeLineHistory (scalar_t__) ; 
 int replication_active ; 
 scalar_t__ sendTimeLine ; 
 int sendTimeLineIsHistoric ; 
 scalar_t__ sendTimeLineNextTLI ; 
 int sendTimeLineValidUpto ; 
 int sentPtr ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int streamingDoneReceiving ; 
 int streamingDoneSending ; 
 int tliSwitchPoint (scalar_t__,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static void
StartReplication(StartReplicationCmd *cmd)
{
	StringInfoData buf;
	XLogRecPtr	FlushPtr;

	if (ThisTimeLineID == 0)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("IDENTIFY_SYSTEM has not been run before START_REPLICATION")));

	/*
	 * We assume here that we're logging enough information in the WAL for
	 * log-shipping, since this is checked in PostmasterMain().
	 *
	 * NOTE: wal_level can only change at shutdown, so in most cases it is
	 * difficult for there to be WAL data that we can still see that was
	 * written at wal_level='minimal'.
	 */

	if (cmd->slotname)
	{
		ReplicationSlotAcquire(cmd->slotname, true);
		if (SlotIsLogical(MyReplicationSlot))
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 (errmsg("cannot use a logical replication slot for physical replication"))));
	}

	/*
	 * Select the timeline. If it was given explicitly by the client, use
	 * that. Otherwise use the timeline of the last replayed record, which is
	 * kept in ThisTimeLineID.
	 */
	if (am_cascading_walsender)
	{
		/* this also updates ThisTimeLineID */
		FlushPtr = GetStandbyFlushRecPtr();
	}
	else
		FlushPtr = GetFlushRecPtr();

	if (cmd->timeline != 0)
	{
		XLogRecPtr	switchpoint;

		sendTimeLine = cmd->timeline;
		if (sendTimeLine == ThisTimeLineID)
		{
			sendTimeLineIsHistoric = false;
			sendTimeLineValidUpto = InvalidXLogRecPtr;
		}
		else
		{
			List	   *timeLineHistory;

			sendTimeLineIsHistoric = true;

			/*
			 * Check that the timeline the client requested exists, and the
			 * requested start location is on that timeline.
			 */
			timeLineHistory = readTimeLineHistory(ThisTimeLineID);
			switchpoint = tliSwitchPoint(cmd->timeline, timeLineHistory,
										 &sendTimeLineNextTLI);
			list_free_deep(timeLineHistory);

			/*
			 * Found the requested timeline in the history. Check that
			 * requested startpoint is on that timeline in our history.
			 *
			 * This is quite loose on purpose. We only check that we didn't
			 * fork off the requested timeline before the switchpoint. We
			 * don't check that we switched *to* it before the requested
			 * starting point. This is because the client can legitimately
			 * request to start replication from the beginning of the WAL
			 * segment that contains switchpoint, but on the new timeline, so
			 * that it doesn't end up with a partial segment. If you ask for
			 * too old a starting point, you'll get an error later when we
			 * fail to find the requested WAL segment in pg_wal.
			 *
			 * XXX: we could be more strict here and only allow a startpoint
			 * that's older than the switchpoint, if it's still in the same
			 * WAL segment.
			 */
			if (!XLogRecPtrIsInvalid(switchpoint) &&
				switchpoint < cmd->startpoint)
			{
				ereport(ERROR,
						(errmsg("requested starting point %X/%X on timeline %u is not in this server's history",
								(uint32) (cmd->startpoint >> 32),
								(uint32) (cmd->startpoint),
								cmd->timeline),
						 errdetail("This server's history forked from timeline %u at %X/%X.",
								   cmd->timeline,
								   (uint32) (switchpoint >> 32),
								   (uint32) (switchpoint))));
			}
			sendTimeLineValidUpto = switchpoint;
		}
	}
	else
	{
		sendTimeLine = ThisTimeLineID;
		sendTimeLineValidUpto = InvalidXLogRecPtr;
		sendTimeLineIsHistoric = false;
	}

	streamingDoneSending = streamingDoneReceiving = false;

	/* If there is nothing to stream, don't even enter COPY mode */
	if (!sendTimeLineIsHistoric || cmd->startpoint < sendTimeLineValidUpto)
	{
		/*
		 * When we first start replication the standby will be behind the
		 * primary. For some applications, for example synchronous
		 * replication, it is important to have a clear state for this initial
		 * catchup mode, so we can trigger actions when we change streaming
		 * state later. We may stay in this state for a long time, which is
		 * exactly why we want to be able to monitor whether or not we are
		 * still here.
		 */
		WalSndSetState(WALSNDSTATE_CATCHUP);

		/* Send a CopyBothResponse message, and start streaming */
		pq_beginmessage(&buf, 'W');
		pq_sendbyte(&buf, 0);
		pq_sendint16(&buf, 0);
		pq_endmessage(&buf);
		pq_flush();

		/*
		 * Don't allow a request to stream from a future point in WAL that
		 * hasn't been flushed to disk in this server yet.
		 */
		if (FlushPtr < cmd->startpoint)
		{
			ereport(ERROR,
					(errmsg("requested starting point %X/%X is ahead of the WAL flush position of this server %X/%X",
							(uint32) (cmd->startpoint >> 32),
							(uint32) (cmd->startpoint),
							(uint32) (FlushPtr >> 32),
							(uint32) (FlushPtr))));
		}

		/* Start streaming from the requested point */
		sentPtr = cmd->startpoint;

		/* Initialize shared memory status, too */
		SpinLockAcquire(&MyWalSnd->mutex);
		MyWalSnd->sentPtr = sentPtr;
		SpinLockRelease(&MyWalSnd->mutex);

		SyncRepInitConfig();

		/* Main loop of walsender */
		replication_active = true;

		WalSndLoop(XLogSendPhysical);

		replication_active = false;
		if (got_STOPPING)
			proc_exit(0);
		WalSndSetState(WALSNDSTATE_STARTUP);

		Assert(streamingDoneSending && streamingDoneReceiving);
	}

	if (cmd->slotname)
		ReplicationSlotRelease();

	/*
	 * Copy is finished now. Send a single-row result set indicating the next
	 * timeline.
	 */
	if (sendTimeLineIsHistoric)
	{
		char		startpos_str[8 + 1 + 8 + 1];
		DestReceiver *dest;
		TupOutputState *tstate;
		TupleDesc	tupdesc;
		Datum		values[2];
		bool		nulls[2];

		snprintf(startpos_str, sizeof(startpos_str), "%X/%X",
				 (uint32) (sendTimeLineValidUpto >> 32),
				 (uint32) sendTimeLineValidUpto);

		dest = CreateDestReceiver(DestRemoteSimple);
		MemSet(nulls, false, sizeof(nulls));

		/*
		 * Need a tuple descriptor representing two columns. int8 may seem
		 * like a surprising data type for this, but in theory int4 would not
		 * be wide enough for this, as TimeLineID is unsigned.
		 */
		tupdesc = CreateTemplateTupleDesc(2);
		TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 1, "next_tli",
								  INT8OID, -1, 0);
		TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 2, "next_tli_startpos",
								  TEXTOID, -1, 0);

		/* prepare for projection of tuple */
		tstate = begin_tup_output_tupdesc(dest, tupdesc, &TTSOpsVirtual);

		values[0] = Int64GetDatum((int64) sendTimeLineNextTLI);
		values[1] = CStringGetTextDatum(startpos_str);

		/* send it to dest */
		do_tup_output(tstate, values, nulls);

		end_tup_output(tstate);
	}

	/* Send CommandComplete message */
	pq_puttextmessage('C', "START_STREAMING");
}