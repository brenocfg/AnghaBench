#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_5__ {scalar_t__ ps_ResultTupleSlot; } ;
struct TYPE_7__ {TYPE_1__ ps; } ;
struct TYPE_6__ {int /*<<< orphan*/  readptr; TYPE_3__ ss; int /*<<< orphan*/ * relation; } ;
typedef  TYPE_2__ NamedTuplestoreScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecScanReScan (TYPE_3__*) ; 
 int /*<<< orphan*/  tuplestore_rescan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_select_read_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecReScanNamedTuplestoreScan(NamedTuplestoreScanState *node)
{
	Tuplestorestate *tuplestorestate = node->relation;

	if (node->ss.ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	ExecScanReScan(&node->ss);

	/*
	 * Rewind my own pointer.
	 */
	tuplestore_select_read_pointer(tuplestorestate, node->readptr);
	tuplestore_rescan(tuplestorestate);
}