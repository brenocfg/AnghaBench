#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_14__ {int /*<<< orphan*/ * ecxt_scantuple; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* RecheckForeignScan ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_5__* ps_ExprContext; } ;
struct TYPE_11__ {TYPE_1__ ps; } ;
struct TYPE_12__ {int /*<<< orphan*/  fdw_recheck_quals; TYPE_2__ ss; TYPE_4__* fdwroutine; } ;
typedef  TYPE_3__ ForeignScanState ;
typedef  TYPE_4__ FdwRoutine ;
typedef  TYPE_5__ ExprContext ;

/* Variables and functions */
 int ExecQual (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ResetExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ForeignRecheck(ForeignScanState *node, TupleTableSlot *slot)
{
	FdwRoutine *fdwroutine = node->fdwroutine;
	ExprContext *econtext;

	/*
	 * extract necessary information from foreign scan node
	 */
	econtext = node->ss.ps.ps_ExprContext;

	/* Does the tuple meet the remote qual condition? */
	econtext->ecxt_scantuple = slot;

	ResetExprContext(econtext);

	/*
	 * If an outer join is pushed down, RecheckForeignScan may need to store a
	 * different tuple in the slot, because a different set of columns may go
	 * to NULL upon recheck.  Otherwise, it shouldn't need to change the slot
	 * contents, just return true or false to indicate whether the quals still
	 * pass.  For simple cases, setting fdw_recheck_quals may be easier than
	 * providing this callback.
	 */
	if (fdwroutine->RecheckForeignScan &&
		!fdwroutine->RecheckForeignScan(node, slot))
		return false;

	return ExecQual(node->fdw_recheck_quals, econtext);
}