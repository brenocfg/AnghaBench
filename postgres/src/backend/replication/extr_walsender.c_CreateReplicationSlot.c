#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xloc ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  int /*<<< orphan*/  TupOutputState ;
struct TYPE_10__ {int confirmed_flush; int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_1__ data; } ;
struct TYPE_12__ {scalar_t__ kind; char const* plugin; scalar_t__ temporary; int /*<<< orphan*/  slotname; } ;
struct TYPE_11__ {int /*<<< orphan*/  snapshot_builder; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ LogicalDecodingContext ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_3__ CreateReplicationSlotCmd ;
typedef  scalar_t__ CRSSnapshotAction ;
typedef  int /*<<< orphan*/  AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CRS_EXPORT_SNAPSHOT ; 
 scalar_t__ CRS_USE_SNAPSHOT ; 
 int /*<<< orphan*/  CStringGetTextDatum (char const*) ; 
 int /*<<< orphan*/  CheckLogicalDecodingRequirements () ; 
 int /*<<< orphan*/ * CreateDestReceiver (int /*<<< orphan*/ ) ; 
 TYPE_2__* CreateInitDecodingContext (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (int) ; 
 int /*<<< orphan*/  DecodingContextFindStartpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  DestRemoteSimple ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ FirstSnapshotSet ; 
 int /*<<< orphan*/  FreeDecodingContext (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 scalar_t__ IsSubTransaction () ; 
 scalar_t__ IsTransactionBlock () ; 
 int MAXFNAMELEN ; 
 int /*<<< orphan*/  MemSet (int*,int,int) ; 
 int /*<<< orphan*/  MyProc ; 
 TYPE_5__* MyReplicationSlot ; 
 int /*<<< orphan*/  NIL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ REPLICATION_KIND_LOGICAL ; 
 scalar_t__ REPLICATION_KIND_PHYSICAL ; 
 int /*<<< orphan*/  RS_EPHEMERAL ; 
 int /*<<< orphan*/  RS_PERSISTENT ; 
 int /*<<< orphan*/  RS_TEMPORARY ; 
 int /*<<< orphan*/  ReplicationSlotCreate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationSlotMarkDirty () ; 
 int /*<<< orphan*/  ReplicationSlotPersist () ; 
 int /*<<< orphan*/  ReplicationSlotRelease () ; 
 int /*<<< orphan*/  ReplicationSlotReserveWal () ; 
 int /*<<< orphan*/  ReplicationSlotSave () ; 
 int /*<<< orphan*/  RestoreTransactionSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* SnapBuildExportSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapBuildInitialSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXTOID ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 int /*<<< orphan*/  ThisTimeLineID ; 
 int /*<<< orphan*/  TupleDescInitBuiltinEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WalSndPrepareWrite ; 
 int /*<<< orphan*/  WalSndUpdateProgress ; 
 int /*<<< orphan*/  WalSndWriteData ; 
 scalar_t__ XACT_REPEATABLE_READ ; 
 scalar_t__ XactIsoLevel ; 
 int /*<<< orphan*/ * begin_tup_output_tupdesc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_tup_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  end_tup_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ last_reply_timestamp ; 
 int /*<<< orphan*/  logical_read_xlog_page ; 
 int /*<<< orphan*/  parseCreateReplSlotOptions (TYPE_3__*,int*,scalar_t__*) ; 
 int /*<<< orphan*/  sendTimeLine ; 
 int sendTimeLineIsHistoric ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static void
CreateReplicationSlot(CreateReplicationSlotCmd *cmd)
{
	const char *snapshot_name = NULL;
	char		xloc[MAXFNAMELEN];
	char	   *slot_name;
	bool		reserve_wal = false;
	CRSSnapshotAction snapshot_action = CRS_EXPORT_SNAPSHOT;
	DestReceiver *dest;
	TupOutputState *tstate;
	TupleDesc	tupdesc;
	Datum		values[4];
	bool		nulls[4];

	Assert(!MyReplicationSlot);

	parseCreateReplSlotOptions(cmd, &reserve_wal, &snapshot_action);

	/* setup state for XLogRead */
	sendTimeLineIsHistoric = false;
	sendTimeLine = ThisTimeLineID;

	if (cmd->kind == REPLICATION_KIND_PHYSICAL)
	{
		ReplicationSlotCreate(cmd->slotname, false,
							  cmd->temporary ? RS_TEMPORARY : RS_PERSISTENT);
	}
	else
	{
		CheckLogicalDecodingRequirements();

		/*
		 * Initially create persistent slot as ephemeral - that allows us to
		 * nicely handle errors during initialization because it'll get
		 * dropped if this transaction fails. We'll make it persistent at the
		 * end. Temporary slots can be created as temporary from beginning as
		 * they get dropped on error as well.
		 */
		ReplicationSlotCreate(cmd->slotname, true,
							  cmd->temporary ? RS_TEMPORARY : RS_EPHEMERAL);
	}

	if (cmd->kind == REPLICATION_KIND_LOGICAL)
	{
		LogicalDecodingContext *ctx;
		bool		need_full_snapshot = false;

		/*
		 * Do options check early so that we can bail before calling the
		 * DecodingContextFindStartpoint which can take long time.
		 */
		if (snapshot_action == CRS_EXPORT_SNAPSHOT)
		{
			if (IsTransactionBlock())
				ereport(ERROR,
				/*- translator: %s is a CREATE_REPLICATION_SLOT statement */
						(errmsg("%s must not be called inside a transaction",
								"CREATE_REPLICATION_SLOT ... EXPORT_SNAPSHOT")));

			need_full_snapshot = true;
		}
		else if (snapshot_action == CRS_USE_SNAPSHOT)
		{
			if (!IsTransactionBlock())
				ereport(ERROR,
				/*- translator: %s is a CREATE_REPLICATION_SLOT statement */
						(errmsg("%s must be called inside a transaction",
								"CREATE_REPLICATION_SLOT ... USE_SNAPSHOT")));

			if (XactIsoLevel != XACT_REPEATABLE_READ)
				ereport(ERROR,
				/*- translator: %s is a CREATE_REPLICATION_SLOT statement */
						(errmsg("%s must be called in REPEATABLE READ isolation mode transaction",
								"CREATE_REPLICATION_SLOT ... USE_SNAPSHOT")));

			if (FirstSnapshotSet)
				ereport(ERROR,
				/*- translator: %s is a CREATE_REPLICATION_SLOT statement */
						(errmsg("%s must be called before any query",
								"CREATE_REPLICATION_SLOT ... USE_SNAPSHOT")));

			if (IsSubTransaction())
				ereport(ERROR,
				/*- translator: %s is a CREATE_REPLICATION_SLOT statement */
						(errmsg("%s must not be called in a subtransaction",
								"CREATE_REPLICATION_SLOT ... USE_SNAPSHOT")));

			need_full_snapshot = true;
		}

		ctx = CreateInitDecodingContext(cmd->plugin, NIL, need_full_snapshot,
										InvalidXLogRecPtr,
										logical_read_xlog_page,
										WalSndPrepareWrite, WalSndWriteData,
										WalSndUpdateProgress);

		/*
		 * Signal that we don't need the timeout mechanism. We're just
		 * creating the replication slot and don't yet accept feedback
		 * messages or send keepalives. As we possibly need to wait for
		 * further WAL the walsender would otherwise possibly be killed too
		 * soon.
		 */
		last_reply_timestamp = 0;

		/* build initial snapshot, might take a while */
		DecodingContextFindStartpoint(ctx);

		/*
		 * Export or use the snapshot if we've been asked to do so.
		 *
		 * NB. We will convert the snapbuild.c kind of snapshot to normal
		 * snapshot when doing this.
		 */
		if (snapshot_action == CRS_EXPORT_SNAPSHOT)
		{
			snapshot_name = SnapBuildExportSnapshot(ctx->snapshot_builder);
		}
		else if (snapshot_action == CRS_USE_SNAPSHOT)
		{
			Snapshot	snap;

			snap = SnapBuildInitialSnapshot(ctx->snapshot_builder);
			RestoreTransactionSnapshot(snap, MyProc);
		}

		/* don't need the decoding context anymore */
		FreeDecodingContext(ctx);

		if (!cmd->temporary)
			ReplicationSlotPersist();
	}
	else if (cmd->kind == REPLICATION_KIND_PHYSICAL && reserve_wal)
	{
		ReplicationSlotReserveWal();

		ReplicationSlotMarkDirty();

		/* Write this slot to disk if it's a permanent one. */
		if (!cmd->temporary)
			ReplicationSlotSave();
	}

	snprintf(xloc, sizeof(xloc), "%X/%X",
			 (uint32) (MyReplicationSlot->data.confirmed_flush >> 32),
			 (uint32) MyReplicationSlot->data.confirmed_flush);

	dest = CreateDestReceiver(DestRemoteSimple);
	MemSet(nulls, false, sizeof(nulls));

	/*----------
	 * Need a tuple descriptor representing four columns:
	 * - first field: the slot name
	 * - second field: LSN at which we became consistent
	 * - third field: exported snapshot's name
	 * - fourth field: output plugin
	 *----------
	 */
	tupdesc = CreateTemplateTupleDesc(4);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 1, "slot_name",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 2, "consistent_point",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 3, "snapshot_name",
							  TEXTOID, -1, 0);
	TupleDescInitBuiltinEntry(tupdesc, (AttrNumber) 4, "output_plugin",
							  TEXTOID, -1, 0);

	/* prepare for projection of tuples */
	tstate = begin_tup_output_tupdesc(dest, tupdesc, &TTSOpsVirtual);

	/* slot_name */
	slot_name = NameStr(MyReplicationSlot->data.name);
	values[0] = CStringGetTextDatum(slot_name);

	/* consistent wal location */
	values[1] = CStringGetTextDatum(xloc);

	/* snapshot name, or NULL if none */
	if (snapshot_name != NULL)
		values[2] = CStringGetTextDatum(snapshot_name);
	else
		nulls[2] = true;

	/* plugin, or NULL if none */
	if (cmd->plugin != NULL)
		values[3] = CStringGetTextDatum(cmd->plugin);
	else
		nulls[3] = true;

	/* send it to dest */
	do_tup_output(tstate, values, nulls);
	end_tup_output(tstate);

	ReplicationSlotRelease();
}