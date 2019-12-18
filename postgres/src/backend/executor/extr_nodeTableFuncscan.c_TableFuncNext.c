#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_6__ {int /*<<< orphan*/  ps_ExprContext; } ;
struct TYPE_7__ {TYPE_1__ ps; int /*<<< orphan*/ * ss_ScanTupleSlot; } ;
struct TYPE_8__ {int /*<<< orphan*/ * tupstore; TYPE_2__ ss; } ;
typedef  TYPE_3__ TableFuncScanState ;

/* Variables and functions */
 int /*<<< orphan*/  tfuncFetchRows (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuplestore_gettupleslot (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TupleTableSlot *
TableFuncNext(TableFuncScanState *node)
{
	TupleTableSlot *scanslot;

	scanslot = node->ss.ss_ScanTupleSlot;

	/*
	 * If first time through, read all tuples from function and put them in a
	 * tuplestore. Subsequent calls just fetch tuples from tuplestore.
	 */
	if (node->tupstore == NULL)
		tfuncFetchRows(node, node->ss.ps.ps_ExprContext);

	/*
	 * Get the next tuple from tuplestore.
	 */
	(void) tuplestore_gettupleslot(node->tupstore,
								   true,
								   false,
								   scanslot);
	return scanslot;
}