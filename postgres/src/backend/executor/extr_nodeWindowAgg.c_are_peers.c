#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ plan; } ;
struct TYPE_9__ {TYPE_1__ ps; } ;
struct TYPE_10__ {int /*<<< orphan*/  ordEqfunction; TYPE_5__* tmpcontext; TYPE_2__ ss; } ;
typedef  TYPE_3__ WindowAggState ;
struct TYPE_11__ {scalar_t__ ordNumCols; } ;
typedef  TYPE_4__ WindowAgg ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_12__ {int /*<<< orphan*/ * ecxt_innertuple; int /*<<< orphan*/ * ecxt_outertuple; } ;
typedef  TYPE_5__ ExprContext ;

/* Variables and functions */
 int ExecQualAndReset (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static bool
are_peers(WindowAggState *winstate, TupleTableSlot *slot1,
		  TupleTableSlot *slot2)
{
	WindowAgg  *node = (WindowAgg *) winstate->ss.ps.plan;
	ExprContext *econtext = winstate->tmpcontext;

	/* If no ORDER BY, all rows are peers with each other */
	if (node->ordNumCols == 0)
		return true;

	econtext->ecxt_outertuple = slot1;
	econtext->ecxt_innertuple = slot2;
	return ExecQualAndReset(winstate->ordEqfunction, econtext);
}