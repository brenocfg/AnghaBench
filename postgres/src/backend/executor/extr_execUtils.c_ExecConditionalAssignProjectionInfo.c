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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_8__ {int resultopsset; int scanopsset; int resultopsfixed; int scanopsfixed; int /*<<< orphan*/ * resultops; int /*<<< orphan*/  ps_ResultTupleSlot; int /*<<< orphan*/ * scanops; int /*<<< orphan*/ * ps_ProjInfo; TYPE_1__* plan; } ;
struct TYPE_7__ {int /*<<< orphan*/  targetlist; } ;
typedef  TYPE_2__ PlanState ;
typedef  int /*<<< orphan*/  Index ;

/* Variables and functions */
 int /*<<< orphan*/  ExecAssignProjectionInfo (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecInitResultSlot (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTSOpsVirtual ; 
 scalar_t__ tlist_matches_tupdesc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecConditionalAssignProjectionInfo(PlanState *planstate, TupleDesc inputDesc,
									Index varno)
{
	if (tlist_matches_tupdesc(planstate,
							  planstate->plan->targetlist,
							  varno,
							  inputDesc))
	{
		planstate->ps_ProjInfo = NULL;
		planstate->resultopsset = planstate->scanopsset;
		planstate->resultopsfixed = planstate->scanopsfixed;
		planstate->resultops = planstate->scanops;
	}
	else
	{
		if (!planstate->ps_ResultTupleSlot)
		{
			ExecInitResultSlot(planstate, &TTSOpsVirtual);
			planstate->resultops = &TTSOpsVirtual;
			planstate->resultopsfixed = true;
			planstate->resultopsset = true;
		}
		ExecAssignProjectionInfo(planstate, inputDesc);
	}
}