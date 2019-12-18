#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ ps_ResultTupleSlot; } ;
struct TYPE_6__ {TYPE_4__ ps; } ;
typedef  TYPE_1__ GatherMergeState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_4__*) ; 
 int /*<<< orphan*/  ExecShutdownGatherMerge (TYPE_1__*) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_1__*) ; 

void
ExecEndGatherMerge(GatherMergeState *node)
{
	ExecEndNode(outerPlanState(node));	/* let children clean up first */
	ExecShutdownGatherMerge(node);
	ExecFreeExprContext(&node->ps);
	if (node->ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ps.ps_ResultTupleSlot);
}