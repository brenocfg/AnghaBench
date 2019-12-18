#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ps_ResultTupleSlot; } ;
struct TYPE_8__ {int /*<<< orphan*/  ss_ScanTupleSlot; TYPE_5__ ps; } ;
struct TYPE_9__ {TYPE_2__ ss; TYPE_1__* methods; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* EndCustomScan ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ CustomScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void
ExecEndCustomScan(CustomScanState *node)
{
	Assert(node->methods->EndCustomScan != NULL);
	node->methods->EndCustomScan(node);

	/* Free the exprcontext */
	ExecFreeExprContext(&node->ss.ps);

	/* Clean out the tuple table */
	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->ss.ss_ScanTupleSlot);
}