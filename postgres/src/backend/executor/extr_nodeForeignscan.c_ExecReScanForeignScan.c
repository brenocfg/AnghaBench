#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  ss; TYPE_1__* fdwroutine; } ;
struct TYPE_10__ {int /*<<< orphan*/ * chgParam; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* ReScanForeignScan ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ PlanState ;
typedef  TYPE_3__ ForeignScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecReScan (TYPE_2__*) ; 
 int /*<<< orphan*/  ExecScanReScan (int /*<<< orphan*/ *) ; 
 TYPE_2__* outerPlanState (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
ExecReScanForeignScan(ForeignScanState *node)
{
	PlanState  *outerPlan = outerPlanState(node);

	node->fdwroutine->ReScanForeignScan(node);

	/*
	 * If chgParam of subnode is not null then plan will be re-scanned by
	 * first ExecProcNode.  outerPlan may also be NULL, in which case there is
	 * nothing to rescan at all.
	 */
	if (outerPlan != NULL && outerPlan->chgParam == NULL)
		ExecReScan(outerPlan);

	ExecScanReScan(&node->ss);
}