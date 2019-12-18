#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int /*<<< orphan*/  ps_ResultTupleDesc; } ;
typedef  TYPE_1__ PlanState ;

/* Variables and functions */

TupleDesc
ExecGetResultType(PlanState *planstate)
{
	return planstate->ps_ResultTupleDesc;
}