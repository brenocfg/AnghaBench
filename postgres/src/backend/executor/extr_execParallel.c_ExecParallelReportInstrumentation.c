#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  instrument; TYPE_1__* plan; } ;
struct TYPE_12__ {int num_plan_nodes; int* plan_node_id; int num_workers; } ;
struct TYPE_11__ {int plan_node_id; } ;
typedef  TYPE_2__ SharedExecutorInstrumentation ;
typedef  TYPE_3__ PlanState ;
typedef  int /*<<< orphan*/  Instrumentation ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/ * GetInstrumentationArray (TYPE_2__*) ; 
 int /*<<< orphan*/  InstrAggNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InstrEndLoop (int /*<<< orphan*/ ) ; 
 int IsParallelWorker () ; 
 size_t ParallelWorkerNumber ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int planstate_tree_walker (TYPE_3__*,int (*) (TYPE_3__*,TYPE_2__*),TYPE_2__*) ; 

__attribute__((used)) static bool
ExecParallelReportInstrumentation(PlanState *planstate,
								  SharedExecutorInstrumentation *instrumentation)
{
	int			i;
	int			plan_node_id = planstate->plan->plan_node_id;
	Instrumentation *instrument;

	InstrEndLoop(planstate->instrument);

	/*
	 * If we shuffled the plan_node_id values in ps_instrument into sorted
	 * order, we could use binary search here.  This might matter someday if
	 * we're pushing down sufficiently large plan trees.  For now, do it the
	 * slow, dumb way.
	 */
	for (i = 0; i < instrumentation->num_plan_nodes; ++i)
		if (instrumentation->plan_node_id[i] == plan_node_id)
			break;
	if (i >= instrumentation->num_plan_nodes)
		elog(ERROR, "plan node %d not found", plan_node_id);

	/*
	 * Add our statistics to the per-node, per-worker totals.  It's possible
	 * that this could happen more than once if we relaunched workers.
	 */
	instrument = GetInstrumentationArray(instrumentation);
	instrument += i * instrumentation->num_workers;
	Assert(IsParallelWorker());
	Assert(ParallelWorkerNumber < instrumentation->num_workers);
	InstrAggNode(&instrument[ParallelWorkerNumber], planstate->instrument);

	return planstate_tree_walker(planstate, ExecParallelReportInstrumentation,
								 instrumentation);
}