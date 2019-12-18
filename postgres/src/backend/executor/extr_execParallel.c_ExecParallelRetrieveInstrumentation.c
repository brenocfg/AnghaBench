#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int num_workers; int /*<<< orphan*/  instrument; } ;
struct TYPE_17__ {TYPE_9__* worker_instrument; TYPE_2__* state; int /*<<< orphan*/  instrument; TYPE_1__* plan; } ;
struct TYPE_16__ {int num_plan_nodes; int* plan_node_id; int num_workers; } ;
struct TYPE_15__ {int /*<<< orphan*/  es_query_cxt; } ;
struct TYPE_14__ {int plan_node_id; } ;
typedef  int /*<<< orphan*/  SortState ;
typedef  TYPE_3__ SharedExecutorInstrumentation ;
typedef  TYPE_4__ PlanState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Instrumentation ;
typedef  int /*<<< orphan*/  HashState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecHashRetrieveInstrumentation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecSortRetrieveInstrumentation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetInstrumentationArray (TYPE_3__*) ; 
 int /*<<< orphan*/  InstrAggNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
#define  T_HashState 129 
#define  T_SortState 128 
 int /*<<< orphan*/  WorkerInstrumentation ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mul_size (int,int) ; 
 int nodeTag (TYPE_4__*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_9__* palloc (scalar_t__) ; 
 int planstate_tree_walker (TYPE_4__*,int (*) (TYPE_4__*,TYPE_3__*),TYPE_3__*) ; 

__attribute__((used)) static bool
ExecParallelRetrieveInstrumentation(PlanState *planstate,
									SharedExecutorInstrumentation *instrumentation)
{
	Instrumentation *instrument;
	int			i;
	int			n;
	int			ibytes;
	int			plan_node_id = planstate->plan->plan_node_id;
	MemoryContext oldcontext;

	/* Find the instrumentation for this node. */
	for (i = 0; i < instrumentation->num_plan_nodes; ++i)
		if (instrumentation->plan_node_id[i] == plan_node_id)
			break;
	if (i >= instrumentation->num_plan_nodes)
		elog(ERROR, "plan node %d not found", plan_node_id);

	/* Accumulate the statistics from all workers. */
	instrument = GetInstrumentationArray(instrumentation);
	instrument += i * instrumentation->num_workers;
	for (n = 0; n < instrumentation->num_workers; ++n)
		InstrAggNode(planstate->instrument, &instrument[n]);

	/*
	 * Also store the per-worker detail.
	 *
	 * Worker instrumentation should be allocated in the same context as the
	 * regular instrumentation information, which is the per-query context.
	 * Switch into per-query memory context.
	 */
	oldcontext = MemoryContextSwitchTo(planstate->state->es_query_cxt);
	ibytes = mul_size(instrumentation->num_workers, sizeof(Instrumentation));
	planstate->worker_instrument =
		palloc(ibytes + offsetof(WorkerInstrumentation, instrument));
	MemoryContextSwitchTo(oldcontext);

	planstate->worker_instrument->num_workers = instrumentation->num_workers;
	memcpy(&planstate->worker_instrument->instrument, instrument, ibytes);

	/* Perform any node-type-specific work that needs to be done. */
	switch (nodeTag(planstate))
	{
		case T_SortState:
			ExecSortRetrieveInstrumentation((SortState *) planstate);
			break;
		case T_HashState:
			ExecHashRetrieveInstrumentation((HashState *) planstate);
			break;
		default:
			break;
	}

	return planstate_tree_walker(planstate, ExecParallelRetrieveInstrumentation,
								 instrumentation);
}