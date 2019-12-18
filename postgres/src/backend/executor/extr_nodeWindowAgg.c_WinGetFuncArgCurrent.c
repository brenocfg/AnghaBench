#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* WindowObject ;
struct TYPE_9__ {TYPE_5__* ps_ExprContext; } ;
struct TYPE_10__ {int /*<<< orphan*/  ss_ScanTupleSlot; TYPE_1__ ps; } ;
struct TYPE_12__ {TYPE_2__ ss; } ;
typedef  TYPE_4__ WindowAggState ;
struct TYPE_13__ {int /*<<< orphan*/  ecxt_outertuple; } ;
struct TYPE_11__ {int /*<<< orphan*/  argstates; TYPE_4__* winstate; } ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_5__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ *,TYPE_5__*,int*) ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_3__*) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 

Datum
WinGetFuncArgCurrent(WindowObject winobj, int argno, bool *isnull)
{
	WindowAggState *winstate;
	ExprContext *econtext;

	Assert(WindowObjectIsValid(winobj));
	winstate = winobj->winstate;

	econtext = winstate->ss.ps.ps_ExprContext;

	econtext->ecxt_outertuple = winstate->ss.ss_ScanTupleSlot;
	return ExecEvalExpr((ExprState *) list_nth(winobj->argstates, argno),
						econtext, isnull);
}