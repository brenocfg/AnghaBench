#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UserMapping ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_20__ {TYPE_11__* state; scalar_t__ plan; } ;
struct TYPE_23__ {TYPE_3__* ss_ScanTupleSlot; int /*<<< orphan*/ * ss_currentRelation; TYPE_1__ ps; } ;
struct TYPE_28__ {TYPE_4__ ss; void* fdw_state; } ;
struct TYPE_27__ {int /*<<< orphan*/  serverid; } ;
struct TYPE_26__ {int num_tuples; int numParams; int /*<<< orphan*/  param_values; int /*<<< orphan*/  param_exprs; int /*<<< orphan*/  param_flinfo; int /*<<< orphan*/  attinmeta; int /*<<< orphan*/ * rel; void* has_returning; int /*<<< orphan*/  temp_cxt; void* set_processed; int /*<<< orphan*/ * retrieved_attrs; int /*<<< orphan*/  query; int /*<<< orphan*/ * resultRel; int /*<<< orphan*/  conn; } ;
struct TYPE_25__ {scalar_t__ checkAsUser; } ;
struct TYPE_24__ {scalar_t__ scanrelid; } ;
struct TYPE_22__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
struct TYPE_21__ {int /*<<< orphan*/  ri_RangeTableIndex; } ;
struct TYPE_19__ {int /*<<< orphan*/  es_query_cxt; TYPE_2__* es_result_relation_info; } ;
struct TYPE_18__ {int /*<<< orphan*/  fdw_exprs; int /*<<< orphan*/  fdw_scan_tlist; TYPE_5__ scan; int /*<<< orphan*/  fdw_private; } ;
typedef  TYPE_6__ RangeTblEntry ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_7__ PgFdwDirectModifyState ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  Index ;
typedef  TYPE_8__ ForeignTable ;
typedef  TYPE_9__ ForeignScanState ;
typedef  TYPE_10__ ForeignScan ;
typedef  TYPE_11__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int EXEC_FLAG_EXPLAIN_ONLY ; 
 int /*<<< orphan*/ * ExecOpenScanRelation (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FdwDirectModifyPrivateHasReturning ; 
 int /*<<< orphan*/  FdwDirectModifyPrivateRetrievedAttrs ; 
 int /*<<< orphan*/  FdwDirectModifyPrivateSetProcessed ; 
 int /*<<< orphan*/  FdwDirectModifyPrivateUpdateSql ; 
 int /*<<< orphan*/  GetConnection (int /*<<< orphan*/ *,int) ; 
 TYPE_8__* GetForeignTable (int /*<<< orphan*/ ) ; 
 scalar_t__ GetUserId () ; 
 int /*<<< orphan*/ * GetUserMapping (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TupleDescGetAttInMetadata (int /*<<< orphan*/ ) ; 
 TYPE_6__* exec_rt_fetch (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  init_returning_filter (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* intVal (scalar_t__) ; 
 int list_length (int /*<<< orphan*/ ) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  prepare_query_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strVal (scalar_t__) ; 

__attribute__((used)) static void
postgresBeginDirectModify(ForeignScanState *node, int eflags)
{
	ForeignScan *fsplan = (ForeignScan *) node->ss.ps.plan;
	EState	   *estate = node->ss.ps.state;
	PgFdwDirectModifyState *dmstate;
	Index		rtindex;
	RangeTblEntry *rte;
	Oid			userid;
	ForeignTable *table;
	UserMapping *user;
	int			numParams;

	/*
	 * Do nothing in EXPLAIN (no ANALYZE) case.  node->fdw_state stays NULL.
	 */
	if (eflags & EXEC_FLAG_EXPLAIN_ONLY)
		return;

	/*
	 * We'll save private state in node->fdw_state.
	 */
	dmstate = (PgFdwDirectModifyState *) palloc0(sizeof(PgFdwDirectModifyState));
	node->fdw_state = (void *) dmstate;

	/*
	 * Identify which user to do the remote access as.  This should match what
	 * ExecCheckRTEPerms() does.
	 */
	rtindex = estate->es_result_relation_info->ri_RangeTableIndex;
	rte = exec_rt_fetch(rtindex, estate);
	userid = rte->checkAsUser ? rte->checkAsUser : GetUserId();

	/* Get info about foreign table. */
	if (fsplan->scan.scanrelid == 0)
		dmstate->rel = ExecOpenScanRelation(estate, rtindex, eflags);
	else
		dmstate->rel = node->ss.ss_currentRelation;
	table = GetForeignTable(RelationGetRelid(dmstate->rel));
	user = GetUserMapping(userid, table->serverid);

	/*
	 * Get connection to the foreign server.  Connection manager will
	 * establish new connection if necessary.
	 */
	dmstate->conn = GetConnection(user, false);

	/* Update the foreign-join-related fields. */
	if (fsplan->scan.scanrelid == 0)
	{
		/* Save info about foreign table. */
		dmstate->resultRel = dmstate->rel;

		/*
		 * Set dmstate->rel to NULL to teach get_returning_data() and
		 * make_tuple_from_result_row() that columns fetched from the remote
		 * server are described by fdw_scan_tlist of the foreign-scan plan
		 * node, not the tuple descriptor for the target relation.
		 */
		dmstate->rel = NULL;
	}

	/* Initialize state variable */
	dmstate->num_tuples = -1;	/* -1 means not set yet */

	/* Get private info created by planner functions. */
	dmstate->query = strVal(list_nth(fsplan->fdw_private,
									 FdwDirectModifyPrivateUpdateSql));
	dmstate->has_returning = intVal(list_nth(fsplan->fdw_private,
											 FdwDirectModifyPrivateHasReturning));
	dmstate->retrieved_attrs = (List *) list_nth(fsplan->fdw_private,
												 FdwDirectModifyPrivateRetrievedAttrs);
	dmstate->set_processed = intVal(list_nth(fsplan->fdw_private,
											 FdwDirectModifyPrivateSetProcessed));

	/* Create context for per-tuple temp workspace. */
	dmstate->temp_cxt = AllocSetContextCreate(estate->es_query_cxt,
											  "postgres_fdw temporary data",
											  ALLOCSET_SMALL_SIZES);

	/* Prepare for input conversion of RETURNING results. */
	if (dmstate->has_returning)
	{
		TupleDesc	tupdesc;

		if (fsplan->scan.scanrelid == 0)
			tupdesc = node->ss.ss_ScanTupleSlot->tts_tupleDescriptor;
		else
			tupdesc = RelationGetDescr(dmstate->rel);

		dmstate->attinmeta = TupleDescGetAttInMetadata(tupdesc);

		/*
		 * When performing an UPDATE/DELETE .. RETURNING on a join directly,
		 * initialize a filter to extract an updated/deleted tuple from a scan
		 * tuple.
		 */
		if (fsplan->scan.scanrelid == 0)
			init_returning_filter(dmstate, fsplan->fdw_scan_tlist, rtindex);
	}

	/*
	 * Prepare for processing of parameters used in remote query, if any.
	 */
	numParams = list_length(fsplan->fdw_exprs);
	dmstate->numParams = numParams;
	if (numParams > 0)
		prepare_query_params((PlanState *) node,
							 fsplan->fdw_exprs,
							 numParams,
							 &dmstate->param_flinfo,
							 &dmstate->param_exprs,
							 &dmstate->param_values);
}