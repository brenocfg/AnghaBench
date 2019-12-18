#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ss_ScanTupleSlot; int /*<<< orphan*/  ps; } ;
struct TYPE_6__ {TYPE_1__ ss; } ;
typedef  int /*<<< orphan*/  PlanState ;
typedef  TYPE_2__ GroupState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecFreeExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outerPlanState (TYPE_2__*) ; 

void
ExecEndGroup(GroupState *node)
{
	PlanState  *outerPlan;

	ExecFreeExprContext(&node->ss.ps);

	/* clean up tuple table */
	ExecClearTuple(node->ss.ss_ScanTupleSlot);

	outerPlan = outerPlanState(node);
	ExecEndNode(outerPlan);
}