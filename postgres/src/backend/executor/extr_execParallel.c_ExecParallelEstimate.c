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
struct TYPE_13__ {int /*<<< orphan*/  pcxt; int /*<<< orphan*/  nnodes; } ;
struct TYPE_12__ {TYPE_1__* plan; } ;
struct TYPE_11__ {int /*<<< orphan*/  parallel_aware; } ;
typedef  int /*<<< orphan*/  SortState ;
typedef  int /*<<< orphan*/  SeqScanState ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  TYPE_3__ ExecParallelEstimateContext ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  int /*<<< orphan*/  BitmapHeapScanState ;
typedef  int /*<<< orphan*/  AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAppendEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecBitmapHeapEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecCustomScanEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecForeignScanEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecHashEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecHashJoinEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecIndexOnlyScanEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecIndexScanEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecSeqScanEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecSortEstimate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
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
 int nodeTag (TYPE_2__*) ; 
 int planstate_tree_walker (TYPE_2__*,int (*) (TYPE_2__*,TYPE_3__*),TYPE_3__*) ; 

__attribute__((used)) static bool
ExecParallelEstimate(PlanState *planstate, ExecParallelEstimateContext *e)
{
	if (planstate == NULL)
		return false;

	/* Count this node. */
	e->nnodes++;

	switch (nodeTag(planstate))
	{
		case T_SeqScanState:
			if (planstate->plan->parallel_aware)
				ExecSeqScanEstimate((SeqScanState *) planstate,
									e->pcxt);
			break;
		case T_IndexScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexScanEstimate((IndexScanState *) planstate,
									  e->pcxt);
			break;
		case T_IndexOnlyScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexOnlyScanEstimate((IndexOnlyScanState *) planstate,
										  e->pcxt);
			break;
		case T_ForeignScanState:
			if (planstate->plan->parallel_aware)
				ExecForeignScanEstimate((ForeignScanState *) planstate,
										e->pcxt);
			break;
		case T_AppendState:
			if (planstate->plan->parallel_aware)
				ExecAppendEstimate((AppendState *) planstate,
								   e->pcxt);
			break;
		case T_CustomScanState:
			if (planstate->plan->parallel_aware)
				ExecCustomScanEstimate((CustomScanState *) planstate,
									   e->pcxt);
			break;
		case T_BitmapHeapScanState:
			if (planstate->plan->parallel_aware)
				ExecBitmapHeapEstimate((BitmapHeapScanState *) planstate,
									   e->pcxt);
			break;
		case T_HashJoinState:
			if (planstate->plan->parallel_aware)
				ExecHashJoinEstimate((HashJoinState *) planstate,
									 e->pcxt);
			break;
		case T_HashState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecHashEstimate((HashState *) planstate, e->pcxt);
			break;
		case T_SortState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecSortEstimate((SortState *) planstate, e->pcxt);
			break;

		default:
			break;
	}

	return planstate_tree_walker(planstate, ExecParallelEstimate, e);
}