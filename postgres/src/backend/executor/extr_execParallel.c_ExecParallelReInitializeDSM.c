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
typedef  int /*<<< orphan*/  SeqScanState ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  ParallelContext ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  int /*<<< orphan*/  BitmapHeapScanState ;
typedef  int /*<<< orphan*/  AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAppendReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecBitmapHeapReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecCustomScanReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecForeignScanReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecHashJoinReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexOnlyScanReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecIndexScanReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecSeqScanReInitializeDSM (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
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
ExecParallelReInitializeDSM(PlanState *planstate,
							ParallelContext *pcxt)
{
	if (planstate == NULL)
		return false;

	/*
	 * Call reinitializers for DSM-using plan nodes.
	 */
	switch (nodeTag(planstate))
	{
		case T_SeqScanState:
			if (planstate->plan->parallel_aware)
				ExecSeqScanReInitializeDSM((SeqScanState *) planstate,
										   pcxt);
			break;
		case T_IndexScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexScanReInitializeDSM((IndexScanState *) planstate,
											 pcxt);
			break;
		case T_IndexOnlyScanState:
			if (planstate->plan->parallel_aware)
				ExecIndexOnlyScanReInitializeDSM((IndexOnlyScanState *) planstate,
												 pcxt);
			break;
		case T_ForeignScanState:
			if (planstate->plan->parallel_aware)
				ExecForeignScanReInitializeDSM((ForeignScanState *) planstate,
											   pcxt);
			break;
		case T_AppendState:
			if (planstate->plan->parallel_aware)
				ExecAppendReInitializeDSM((AppendState *) planstate, pcxt);
			break;
		case T_CustomScanState:
			if (planstate->plan->parallel_aware)
				ExecCustomScanReInitializeDSM((CustomScanState *) planstate,
											  pcxt);
			break;
		case T_BitmapHeapScanState:
			if (planstate->plan->parallel_aware)
				ExecBitmapHeapReInitializeDSM((BitmapHeapScanState *) planstate,
											  pcxt);
			break;
		case T_HashJoinState:
			if (planstate->plan->parallel_aware)
				ExecHashJoinReInitializeDSM((HashJoinState *) planstate,
											pcxt);
			break;
		case T_HashState:
		case T_SortState:
			/* these nodes have DSM state, but no reinitialization is required */
			break;

		default:
			break;
	}

	return planstate_tree_walker(planstate, ExecParallelReInitializeDSM, pcxt);
}