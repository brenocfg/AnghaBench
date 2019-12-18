#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ ps_ResultTupleSlot; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {int mt_nplans; int /*<<< orphan*/ * mt_plans; int /*<<< orphan*/  mt_epqstate; TYPE_5__ ps; scalar_t__ mt_root_tuple_slot; scalar_t__ mt_partition_tuple_routing; TYPE_2__* resultRelInfo; } ;
struct TYPE_9__ {TYPE_1__* ri_FdwRoutine; int /*<<< orphan*/  ri_usesFdwDirectModify; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* EndForeignModify ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ ResultRelInfo ;
typedef  TYPE_3__ ModifyTableState ;

/* Variables and functions */
 int /*<<< orphan*/  EvalPlanQualEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecCleanupTupleRouting (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (scalar_t__) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
ExecEndModifyTable(ModifyTableState *node)
{
	int			i;

	/*
	 * Allow any FDWs to shut down
	 */
	for (i = 0; i < node->mt_nplans; i++)
	{
		ResultRelInfo *resultRelInfo = node->resultRelInfo + i;

		if (!resultRelInfo->ri_usesFdwDirectModify &&
			resultRelInfo->ri_FdwRoutine != NULL &&
			resultRelInfo->ri_FdwRoutine->EndForeignModify != NULL)
			resultRelInfo->ri_FdwRoutine->EndForeignModify(node->ps.state,
														   resultRelInfo);
	}

	/*
	 * Close all the partitioned tables, leaf partitions, and their indices
	 * and release the slot used for tuple routing, if set.
	 */
	if (node->mt_partition_tuple_routing)
	{
		ExecCleanupTupleRouting(node, node->mt_partition_tuple_routing);

		if (node->mt_root_tuple_slot)
			ExecDropSingleTupleTableSlot(node->mt_root_tuple_slot);
	}

	/*
	 * Free the exprcontext
	 */
	ExecFreeExprContext(&node->ps);

	/*
	 * clean out the tuple table
	 */
	if (node->ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ps.ps_ResultTupleSlot);

	/*
	 * Terminate EPQ execution if active
	 */
	EvalPlanQualEnd(&node->mt_epqstate);

	/*
	 * shut down subplans
	 */
	for (i = 0; i < node->mt_nplans; i++)
		ExecEndNode(node->mt_plans[i]);
}