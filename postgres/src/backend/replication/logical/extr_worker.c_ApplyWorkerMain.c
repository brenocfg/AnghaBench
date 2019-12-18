#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  originname ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_8__ {int /*<<< orphan*/  publication_names; int /*<<< orphan*/  proto_version; } ;
struct TYPE_9__ {TYPE_1__ logical; } ;
struct TYPE_10__ {int logical; char* slotname; TYPE_2__ proto; int /*<<< orphan*/  startpoint; } ;
typedef  TYPE_3__ WalRcvStreamOptions ;
typedef  int /*<<< orphan*/  TimeLineID ;
struct TYPE_12__ {char* subid; int /*<<< orphan*/  relid; int /*<<< orphan*/  userid; int /*<<< orphan*/  dbid; int /*<<< orphan*/  reply_time; int /*<<< orphan*/  last_recv_time; int /*<<< orphan*/  last_send_time; } ;
struct TYPE_11__ {char* name; char* synccommit; char* slotname; int oid; int /*<<< orphan*/  publications; int /*<<< orphan*/  conninfo; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  RepOriginId ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ApplyContext ; 
 int /*<<< orphan*/  BackgroundWorkerInitializeConnectionByOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 TYPE_5__* GetSubscription (char*,int) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LOGICALREP_PROTO_VERSION_NUM ; 
 int /*<<< orphan*/  LogicalRepApplyLoop (int /*<<< orphan*/ ) ; 
 char* LogicalRepSyncTableStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_6__* MyLogicalRepWorker ; 
 TYPE_5__* MySubscription ; 
 int MySubscriptionValid ; 
 int NAMEDATALEN ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGC_BACKEND ; 
 int /*<<< orphan*/  PGC_SUSET ; 
 int /*<<< orphan*/  PGC_S_OVERRIDE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SUBSCRIPTIONOID ; 
 int /*<<< orphan*/  SUBSCRIPTIONRELMAP ; 
 int /*<<< orphan*/  SetConfigOption (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 scalar_t__ am_tablesync_worker () ; 
 int /*<<< orphan*/  die ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_syncing_table_states ; 
 int /*<<< orphan*/  load_file (char*,int) ; 
 int /*<<< orphan*/  logicalrep_worker_attach (int) ; 
 int /*<<< orphan*/  logicalrep_worker_sighup ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int /*<<< orphan*/ ) ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  replorigin_by_name (char*,int) ; 
 int /*<<< orphan*/  replorigin_create (char*) ; 
 int /*<<< orphan*/  replorigin_session_get_progress (int) ; 
 int /*<<< orphan*/  replorigin_session_origin ; 
 int /*<<< orphan*/  replorigin_session_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  subscription_change_cb ; 
 int /*<<< orphan*/ * walrcv_connect (int /*<<< orphan*/ ,int,char*,char**) ; 
 int /*<<< orphan*/  walrcv_identify_system (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walrcv_startstreaming (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * wrconn ; 

void
ApplyWorkerMain(Datum main_arg)
{
	int			worker_slot = DatumGetInt32(main_arg);
	MemoryContext oldctx;
	char		originname[NAMEDATALEN];
	XLogRecPtr	origin_startpos;
	char	   *myslotname;
	WalRcvStreamOptions options;

	/* Attach to slot */
	logicalrep_worker_attach(worker_slot);

	/* Setup signal handling */
	pqsignal(SIGHUP, logicalrep_worker_sighup);
	pqsignal(SIGTERM, die);
	BackgroundWorkerUnblockSignals();

	/*
	 * We don't currently need any ResourceOwner in a walreceiver process, but
	 * if we did, we could call CreateAuxProcessResourceOwner here.
	 */

	/* Initialise stats to a sanish value */
	MyLogicalRepWorker->last_send_time = MyLogicalRepWorker->last_recv_time =
		MyLogicalRepWorker->reply_time = GetCurrentTimestamp();

	/* Load the libpq-specific functions */
	load_file("libpqwalreceiver", false);

	/* Run as replica session replication role. */
	SetConfigOption("session_replication_role", "replica",
					PGC_SUSET, PGC_S_OVERRIDE);

	/* Connect to our database. */
	BackgroundWorkerInitializeConnectionByOid(MyLogicalRepWorker->dbid,
											  MyLogicalRepWorker->userid,
											  0);

	/* Load the subscription into persistent memory context. */
	ApplyContext = AllocSetContextCreate(TopMemoryContext,
										 "ApplyContext",
										 ALLOCSET_DEFAULT_SIZES);
	StartTransactionCommand();
	oldctx = MemoryContextSwitchTo(ApplyContext);

	MySubscription = GetSubscription(MyLogicalRepWorker->subid, true);
	if (!MySubscription)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription %u will not "
						"start because the subscription was removed during startup",
						MyLogicalRepWorker->subid)));
		proc_exit(0);
	}

	MySubscriptionValid = true;
	MemoryContextSwitchTo(oldctx);

	if (!MySubscription->enabled)
	{
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" will not "
						"start because the subscription was disabled during startup",
						MySubscription->name)));

		proc_exit(0);
	}

	/* Setup synchronous commit according to the user's wishes */
	SetConfigOption("synchronous_commit", MySubscription->synccommit,
					PGC_BACKEND, PGC_S_OVERRIDE);

	/* Keep us informed about subscription changes. */
	CacheRegisterSyscacheCallback(SUBSCRIPTIONOID,
								  subscription_change_cb,
								  (Datum) 0);

	if (am_tablesync_worker())
		ereport(LOG,
				(errmsg("logical replication table synchronization worker for subscription \"%s\", table \"%s\" has started",
						MySubscription->name, get_rel_name(MyLogicalRepWorker->relid))));
	else
		ereport(LOG,
				(errmsg("logical replication apply worker for subscription \"%s\" has started",
						MySubscription->name)));

	CommitTransactionCommand();

	/* Connect to the origin and start the replication. */
	elog(DEBUG1, "connecting to publisher using connection string \"%s\"",
		 MySubscription->conninfo);

	if (am_tablesync_worker())
	{
		char	   *syncslotname;

		/* This is table synchronization worker, call initial sync. */
		syncslotname = LogicalRepSyncTableStart(&origin_startpos);

		/* The slot name needs to be allocated in permanent memory context. */
		oldctx = MemoryContextSwitchTo(ApplyContext);
		myslotname = pstrdup(syncslotname);
		MemoryContextSwitchTo(oldctx);

		pfree(syncslotname);
	}
	else
	{
		/* This is main apply worker */
		RepOriginId originid;
		TimeLineID	startpointTLI;
		char	   *err;

		myslotname = MySubscription->slotname;

		/*
		 * This shouldn't happen if the subscription is enabled, but guard
		 * against DDL bugs or manual catalog changes.  (libpqwalreceiver will
		 * crash if slot is NULL.)
		 */
		if (!myslotname)
			ereport(ERROR,
					(errmsg("subscription has no replication slot set")));

		/* Setup replication origin tracking. */
		StartTransactionCommand();
		snprintf(originname, sizeof(originname), "pg_%u", MySubscription->oid);
		originid = replorigin_by_name(originname, true);
		if (!OidIsValid(originid))
			originid = replorigin_create(originname);
		replorigin_session_setup(originid);
		replorigin_session_origin = originid;
		origin_startpos = replorigin_session_get_progress(false);
		CommitTransactionCommand();

		wrconn = walrcv_connect(MySubscription->conninfo, true, MySubscription->name,
								&err);
		if (wrconn == NULL)
			ereport(ERROR,
					(errmsg("could not connect to the publisher: %s", err)));

		/*
		 * We don't really use the output identify_system for anything but it
		 * does some initializations on the upstream so let's still call it.
		 */
		(void) walrcv_identify_system(wrconn, &startpointTLI);

	}

	/*
	 * Setup callback for syscache so that we know when something changes in
	 * the subscription relation state.
	 */
	CacheRegisterSyscacheCallback(SUBSCRIPTIONRELMAP,
								  invalidate_syncing_table_states,
								  (Datum) 0);

	/* Build logical replication streaming options. */
	options.logical = true;
	options.startpoint = origin_startpos;
	options.slotname = myslotname;
	options.proto.logical.proto_version = LOGICALREP_PROTO_VERSION_NUM;
	options.proto.logical.publication_names = MySubscription->publications;

	/* Start normal logical streaming replication. */
	walrcv_startstreaming(wrconn, &options);

	/* Run the main loop. */
	LogicalRepApplyLoop(origin_startpos);

	proc_exit(0);
}