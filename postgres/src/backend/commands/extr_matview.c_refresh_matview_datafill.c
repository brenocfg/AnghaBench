#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
struct TYPE_10__ {TYPE_1__* estate; } ;
struct TYPE_9__ {int /*<<< orphan*/  es_processed; } ;
typedef  TYPE_2__ QueryDesc ;
typedef  int /*<<< orphan*/  Query ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireRewriteLocks (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 TYPE_2__* CreateQueryDesc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecutorEnd (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecutorFinish (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecutorRun (TYPE_2__*,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  ExecutorStart (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  FreeQueryDesc (TYPE_2__*) ; 
 int /*<<< orphan*/  GetActiveSnapshot () ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushCopiedSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * QueryRewrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UpdateActiveSnapshotCommandId () ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ linitial (int /*<<< orphan*/ *) ; 
 int list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_plan_query (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64
refresh_matview_datafill(DestReceiver *dest, Query *query,
						 const char *queryString)
{
	List	   *rewritten;
	PlannedStmt *plan;
	QueryDesc  *queryDesc;
	Query	   *copied_query;
	uint64		processed;

	/* Lock and rewrite, using a copy to preserve the original query. */
	copied_query = copyObject(query);
	AcquireRewriteLocks(copied_query, true, false);
	rewritten = QueryRewrite(copied_query);

	/* SELECT should never rewrite to more or less than one SELECT query */
	if (list_length(rewritten) != 1)
		elog(ERROR, "unexpected rewrite result for REFRESH MATERIALIZED VIEW");
	query = (Query *) linitial(rewritten);

	/* Check for user-requested abort. */
	CHECK_FOR_INTERRUPTS();

	/* Plan the query which will generate data for the refresh. */
	plan = pg_plan_query(query, 0, NULL);

	/*
	 * Use a snapshot with an updated command ID to ensure this query sees
	 * results of any previously executed queries.  (This could only matter if
	 * the planner executed an allegedly-stable function that changed the
	 * database contents, but let's do it anyway to be safe.)
	 */
	PushCopiedSnapshot(GetActiveSnapshot());
	UpdateActiveSnapshotCommandId();

	/* Create a QueryDesc, redirecting output to our tuple receiver */
	queryDesc = CreateQueryDesc(plan, queryString,
								GetActiveSnapshot(), InvalidSnapshot,
								dest, NULL, NULL, 0);

	/* call ExecutorStart to prepare the plan for execution */
	ExecutorStart(queryDesc, 0);

	/* run the plan */
	ExecutorRun(queryDesc, ForwardScanDirection, 0L, true);

	processed = queryDesc->estate->es_processed;

	/* and clean up */
	ExecutorFinish(queryDesc);
	ExecutorEnd(queryDesc);

	FreeQueryDesc(queryDesc);

	PopActiveSnapshot();

	return processed;
}