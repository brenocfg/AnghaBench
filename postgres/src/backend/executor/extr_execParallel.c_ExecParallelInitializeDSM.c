#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t nnodes; int /*<<< orphan*/  pcxt; TYPE_1__* instrumentation; } ;
struct TYPE_14__ {TYPE_2__* plan; } ;
struct TYPE_13__ {int /*<<< orphan*/  parallel_aware; int /*<<< orphan*/  plan_node_id; } ;
struct TYPE_12__ {int /*<<< orphan*/ * plan_node_id; } ;
typedef  int /*<<< orphan*/  SortState ;
typedef  int /*<<< orphan*/  SeqScanState ;
typedef  TYPE_3__ PlanState ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  TYPE_4__ ExecParallelInitializeDSMContext ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  int /*<<< orphan*/  BitmapHeapScanState ;
typedef  int /*<<< orphan*/  AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAppendInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecBitmapHeapInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCustomScanInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecForeignScanInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecHashInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecHashJoinInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecIndexOnlyScanInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecIndexScanInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecSeqScanInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecSortInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  T_AppendState 137 
#define  T_BitmapHeapScanState 136 
#define  T_CustomScanState 135 
#define  T_ForeignScanState 134 
#define  T_HashJoinState 133 
#define  T_HashState 132 
#define  T_IndexOnlyScanState 131 
#define  T_IndexScanState 130 
#define  T_SeqScanState 129 
#define  T_SortState 128 
 int nodeTag (TYPE_3__*) ; 
 int planstate_tree_walker (TYPE_3__*,int (*) (TYPE_3__*,TYPE_4__*),TYPE_4__*) ; 

__attribute__((used)) static bool
ExecParallelInitializeDSM(PlanState *planstate,
						  ExecParallelInitializeDSMContext *d)
{
	if (planstate == NULL)
		return false;

	/* If instrumentation is enabled, initialize slot for this node. */
	if (d->instrumentation != NULL)
		d->instrumentation->plan_node_id[d->nnodes] =
			planstate->plan->plan_node_id;

	/* Count this node. */
	d->nnodes++;

	/*
	 * Call initializers for DSM-using plan nodes.
	 *
	 * Most plan nodes won't do anything here, but plan nodes that allocated
	 * DSM may need to initialize shared state in the DSM before parallel
	 * workers are launched.  They can allocate the space they previously
	 * estimated using shm_toc_allocate, and add the keys they previously
	 * estimated using shm_toc_insert, in each case targeting pcxt->toc.
	 */
	switch (nodeTag(planstate))
	{
		case T_SeqScanState:
			if (planstate->plan->parallel_aware)
				ExecSeqScanInitializeDSM((SeqScanState *) planstate,
										 d->pcxt);
			break;
		case T_IndexScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexScanInitializeDSM((IndexScanState *) planstate,
										   d->pcxt);
			break;
		case T_IndexOnlyScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexOnlyScanInitializeDSM((IndexOnlyScanState *) planstate,
											   d->pcxt);
			break;
		case T_ForeignScanState:
			if (planstate->plan->parallel_aware)
				ExecForeignScanInitializeDSM((ForeignScanState *) planstate,
											 d->pcxt);
			break;
		case T_AppendState:
			if (planstate->plan->parallel_aware)
				ExecAppendInitializeDSM((AppendState *) planstate,
										d->pcxt);
			break;
		case T_CustomScanState:
			if (planstate->plan->parallel_aware)
				ExecCustomScanInitializeDSM((CustomScanState *) planstate,
											d->pcxt);
			break;
		case T_BitmapHeapScanState:
			if (planstate->plan->parallel_aware)
				ExecBitmapHeapInitializeDSM((BitmapHeapScanState *) planstate,
											d->pcxt);
			break;
		case T_HashJoinState:
			if (planstate->plan->parallel_aware)
				ExecHashJoinInitializeDSM((HashJoinState *) planstate,
										  d->pcxt);
			break;
		case T_HashState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecHashInitializeDSM((HashState *) planstate, d->pcxt);
			break;
		case T_SortState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecSortInitializeDSM((SortState *) planstate, d->pcxt);
			break;

		default:
			break;
	}

	return planstate_tree_walker(planstate, ExecParallelInitializeDSM, d);
}