#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ps_ResultTupleSlot; } ;
struct TYPE_7__ {TYPE_5__ ps; } ;
struct TYPE_8__ {int /*<<< orphan*/  mj_MarkedTupleSlot; TYPE_1__ js; } ;
typedef  TYPE_2__ MergeJoinState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  MJ1_printf (char*,char*) ; 
 int /*<<< orphan*/  innerPlanState (TYPE_2__*) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_2__*) ; 

void
ExecEndMergeJoin(MergeJoinState *node)
{
	MJ1_printf("ExecEndMergeJoin: %s\n",
			   "ending node processing");

	/*
	 * Free the exprcontext
	 */
	ExecFreeExprContext(&node->js.ps);

	/*
	 * clean out the tuple table
	 */
	ExecClearTuple(node->js.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->mj_MarkedTupleSlot);

	/*
	 * shut down the subplans
	 */
	ExecEndNode(innerPlanState(node));
	ExecEndNode(outerPlanState(node));

	MJ1_printf("ExecEndMergeJoin: %s\n",
			   "node processing ended");
}