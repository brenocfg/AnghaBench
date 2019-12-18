#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ commandType; } ;
typedef  TYPE_1__ Query ;
typedef  int /*<<< orphan*/  PlannedStmt ;
typedef  int /*<<< orphan*/  ParamListInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveSnapshotSet () ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CMD_UTILITY ; 
 int /*<<< orphan*/  Debug_pretty_print ; 
 scalar_t__ Debug_print_plan ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ResetUsage () ; 
 int /*<<< orphan*/  ShowUsage (char*) ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_PLAN_DONE () ; 
 int /*<<< orphan*/  TRACE_POSTGRESQL_QUERY_PLAN_START () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/ * copyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  elog_node_display (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ log_planner_stats ; 
 char* nodeToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/ * planner (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stringToNodeWithLocations (char*) ; 

PlannedStmt *
pg_plan_query(Query *querytree, int cursorOptions, ParamListInfo boundParams)
{
	PlannedStmt *plan;

	/* Utility commands have no plans. */
	if (querytree->commandType == CMD_UTILITY)
		return NULL;

	/* Planner must have a snapshot in case it calls user-defined functions. */
	Assert(ActiveSnapshotSet());

	TRACE_POSTGRESQL_QUERY_PLAN_START();

	if (log_planner_stats)
		ResetUsage();

	/* call the optimizer */
	plan = planner(querytree, cursorOptions, boundParams);

	if (log_planner_stats)
		ShowUsage("PLANNER STATISTICS");

#ifdef COPY_PARSE_PLAN_TREES
	/* Optional debugging check: pass plan tree through copyObject() */
	{
		PlannedStmt *new_plan = copyObject(plan);

		/*
		 * equal() currently does not have routines to compare Plan nodes, so
		 * don't try to test equality here.  Perhaps fix someday?
		 */
#ifdef NOT_USED
		/* This checks both copyObject() and the equal() routines... */
		if (!equal(new_plan, plan))
			elog(WARNING, "copyObject() failed to produce an equal plan tree");
		else
#endif
			plan = new_plan;
	}
#endif

#ifdef WRITE_READ_PARSE_PLAN_TREES
	/* Optional debugging check: pass plan tree through outfuncs/readfuncs */
	{
		char	   *str;
		PlannedStmt *new_plan;

		str = nodeToString(plan);
		new_plan = stringToNodeWithLocations(str);
		pfree(str);

		/*
		 * equal() currently does not have routines to compare Plan nodes, so
		 * don't try to test equality here.  Perhaps fix someday?
		 */
#ifdef NOT_USED
		/* This checks both outfuncs/readfuncs and the equal() routines... */
		if (!equal(new_plan, plan))
			elog(WARNING, "outfuncs/readfuncs failed to produce an equal plan tree");
		else
#endif
			plan = new_plan;
	}
#endif

	/*
	 * Print plan if debugging.
	 */
	if (Debug_print_plan)
		elog_node_display(LOG, "plan", plan, Debug_pretty_print);

	TRACE_POSTGRESQL_QUERY_PLAN_DONE();

	return plan;
}