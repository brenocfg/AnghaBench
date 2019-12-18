#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_9__ {scalar_t__ ps_ResultTupleSlot; } ;
struct TYPE_11__ {TYPE_3__ ps; } ;
struct TYPE_10__ {int /*<<< orphan*/  readptr; TYPE_2__* leader; TYPE_5__ ss; } ;
struct TYPE_8__ {int eof_cte; TYPE_1__* cteplanstate; int /*<<< orphan*/ * cte_table; } ;
struct TYPE_7__ {int /*<<< orphan*/ * chgParam; } ;
typedef  TYPE_4__ CteScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecScanReScan (TYPE_5__*) ; 
 int /*<<< orphan*/  tuplestore_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_rescan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecReScanCteScan(CteScanState *node)
{
	Tuplestorestate *tuplestorestate = node->leader->cte_table;

	if (node->ss.ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	ExecScanReScan(&node->ss);

	/*
	 * Clear the tuplestore if a new scan of the underlying CTE is required.
	 * This implicitly resets all the tuplestore's read pointers.  Note that
	 * multiple CTE nodes might redundantly clear the tuplestore; that's OK,
	 * and not unduly expensive.  We'll stop taking this path as soon as
	 * somebody has attempted to read something from the underlying CTE
	 * (thereby causing its chgParam to be cleared).
	 */
	if (node->leader->cteplanstate->chgParam != NULL)
	{
		tuplestore_clear(tuplestorestate);
		node->leader->eof_cte = false;
	}
	else
	{
		/*
		 * Else, just rewind my own pointer.  Either the underlying CTE
		 * doesn't need a rescan (and we can re-read what's in the tuplestore
		 * now), or somebody else already took care of it.
		 */
		tuplestore_select_read_pointer(tuplestorestate, node->readptr);
		tuplestore_rescan(tuplestorestate);
	}
}