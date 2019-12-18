#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {int /*<<< orphan*/  ps_ResultTupleDesc; TYPE_1__* plan; } ;
struct TYPE_4__ {int /*<<< orphan*/  targetlist; } ;
typedef  TYPE_2__ PlanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecTypeFromTL (int /*<<< orphan*/ ) ; 

void
ExecInitResultTypeTL(PlanState *planstate)
{
	TupleDesc	tupDesc = ExecTypeFromTL(planstate->plan->targetlist);

	planstate->ps_ResultTupleDesc = tupDesc;
}