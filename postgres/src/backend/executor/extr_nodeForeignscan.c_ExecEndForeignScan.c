#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ ps_ResultTupleSlot; scalar_t__ plan; } ;
struct TYPE_13__ {scalar_t__ operation; } ;
struct TYPE_11__ {scalar_t__ ss_ScanTupleSlot; TYPE_8__ ps; } ;
struct TYPE_12__ {TYPE_2__ ss; TYPE_1__* fdwroutine; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* EndForeignScan ) (TYPE_3__*) ;int /*<<< orphan*/  (* EndDirectModify ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ ForeignScan ;

/* Variables and functions */
 scalar_t__ CMD_SELECT ; 
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecEndNode (scalar_t__) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_8__*) ; 
 scalar_t__ outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void
ExecEndForeignScan(ForeignScanState *node)
{
	ForeignScan *plan = (ForeignScan *) node->ss.ps.plan;

	/* Let the FDW shut down */
	if (plan->operation != CMD_SELECT)
		node->fdwroutine->EndDirectModify(node);
	else
		node->fdwroutine->EndForeignScan(node);

	/* Shut down any outer plan. */
	if (outerPlanState(node))
		ExecEndNode(outerPlanState(node));

	/* Free the exprcontext */
	ExecFreeExprContext(&node->ss.ps);

	/* clean out the tuple table */
	if (node->ss.ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->ss.ss_ScanTupleSlot);
}