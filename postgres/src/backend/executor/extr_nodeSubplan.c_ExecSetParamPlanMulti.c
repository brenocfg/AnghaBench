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
struct TYPE_6__ {TYPE_1__* ecxt_param_exec_vals; } ;
struct TYPE_5__ {int /*<<< orphan*/ * execPlan; } ;
typedef  TYPE_1__ ParamExecData ;
typedef  TYPE_2__ ExprContext ;
typedef  int /*<<< orphan*/  Bitmapset ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecSetParamPlan (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int bms_next_member (int /*<<< orphan*/  const*,int) ; 

void
ExecSetParamPlanMulti(const Bitmapset *params, ExprContext *econtext)
{
	int			paramid;

	paramid = -1;
	while ((paramid = bms_next_member(params, paramid)) >= 0)
	{
		ParamExecData *prm = &(econtext->ecxt_param_exec_vals[paramid]);

		if (prm->execPlan != NULL)
		{
			/* Parameter not evaluated yet, so go do it */
			ExecSetParamPlan(prm->execPlan, econtext);
			/* ExecSetParamPlan should have processed this param... */
			Assert(prm->execPlan == NULL);
		}
	}
}