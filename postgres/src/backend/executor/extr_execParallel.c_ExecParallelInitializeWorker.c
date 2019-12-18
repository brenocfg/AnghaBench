#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* plan; } ;
struct TYPE_7__ {int /*<<< orphan*/  parallel_aware; } ;
typedef  int /*<<< orphan*/  SortState ;
typedef  int /*<<< orphan*/  SeqScanState ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  ParallelWorkerContext ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  int /*<<< orphan*/  BitmapHeapScanState ;
typedef  int /*<<< orphan*/  AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAppendInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecBitmapHeapInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecCustomScanInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForeignScanInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecHashInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecHashJoinInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexOnlyScanInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexScanInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecSeqScanInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecSortInitializeWorker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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
 int planstate_tree_walker (TYPE_2__*,int (*) (TYPE_2__*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ExecParallelInitializeWorker(PlanState *planstate, ParallelWorkerContext *pwcxt)
{
	if (planstate == NULL)
		return false;

	switch (nodeTag(planstate))
	{
		case T_SeqScanState:
			if (planstate->plan->parallel_aware)
				ExecSeqScanInitializeWorker((SeqScanState *) planstate, pwcxt);
			break;
		case T_IndexScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexScanInitializeWorker((IndexScanState *) planstate,
											  pwcxt);
			break;
		case T_IndexOnlyScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexOnlyScanInitializeWorker((IndexOnlyScanState *) planstate,
												  pwcxt);
			break;
		case T_ForeignScanState:
			if (planstate->plan->parallel_aware)
				ExecForeignScanInitializeWorker((ForeignScanState *) planstate,
												pwcxt);
			break;
		case T_AppendState:
			if (planstate->plan->parallel_aware)
				ExecAppendInitializeWorker((AppendState *) planstate, pwcxt);
			break;
		case T_CustomScanState:
			if (planstate->plan->parallel_aware)
				ExecCustomScanInitializeWorker((CustomScanState *) planstate,
											   pwcxt);
			break;
		case T_BitmapHeapScanState:
			if (planstate->plan->parallel_aware)
				ExecBitmapHeapInitializeWorker((BitmapHeapScanState *) planstate,
											   pwcxt);
			break;
		case T_HashJoinState:
			if (planstate->plan->parallel_aware)
				ExecHashJoinInitializeWorker((HashJoinState *) planstate,
											 pwcxt);
			break;
		case T_HashState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecHashInitializeWorker((HashState *) planstate, pwcxt);
			break;
		case T_SortState:
			/* even when not parallel-aware, for EXPLAIN ANALYZE */
			ExecSortInitializeWorker((SortState *) planstate, pwcxt);
			break;

		default:
			break;
	}

	return planstate_tree_walker(planstate, ExecParallelInitializeWorker,
								 pwcxt);
}