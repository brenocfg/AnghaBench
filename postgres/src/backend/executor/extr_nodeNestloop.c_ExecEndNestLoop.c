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
struct TYPE_8__ {TYPE_1__ js; } ;
typedef  TYPE_2__ NestLoopState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  NL1_printf (char*,char*) ; 
 int /*<<< orphan*/  innerPlanState (TYPE_2__*) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_2__*) ; 

void
ExecEndNestLoop(NestLoopState *node)
{
	NL1_printf("ExecEndNestLoop: %s\n",
			   "ending node processing");

	/*
	 * Free the exprcontext
	 */
	ExecFreeExprContext(&node->js.ps);

	/*
	 * clean out the tuple table
	 */
	ExecClearTuple(node->js.ps.ps_ResultTupleSlot);

	/*
	 * close down subplans
	 */
	ExecEndNode(outerPlanState(node));
	ExecEndNode(innerPlanState(node));

	NL1_printf("ExecEndNestLoop: %s\n",
			   "node processing ended");
}