#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_8__ {scalar_t__ ps_ResultTupleSlot; } ;
struct TYPE_6__ {scalar_t__ ss_ScanTupleSlot; TYPE_4__ ps; int /*<<< orphan*/  ss_currentScanDesc; } ;
struct TYPE_7__ {scalar_t__ vmbuffer; scalar_t__ pvmbuffer; scalar_t__ shared_prefetch_iterator; scalar_t__ shared_tbmiterator; scalar_t__ tbm; scalar_t__ prefetch_iterator; scalar_t__ tbmiterator; TYPE_1__ ss; } ;
typedef  TYPE_2__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecEndNode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_4__*) ; 
 scalar_t__ InvalidBuffer ; 
 int /*<<< orphan*/  ReleaseBuffer (scalar_t__) ; 
 int /*<<< orphan*/  outerPlanState (TYPE_2__*) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_end_iterate (scalar_t__) ; 
 int /*<<< orphan*/  tbm_end_shared_iterate (scalar_t__) ; 
 int /*<<< orphan*/  tbm_free (scalar_t__) ; 

void
ExecEndBitmapHeapScan(BitmapHeapScanState *node)
{
	TableScanDesc scanDesc;

	/*
	 * extract information from the node
	 */
	scanDesc = node->ss.ss_currentScanDesc;

	/*
	 * Free the exprcontext
	 */
	ExecFreeExprContext(&node->ss.ps);

	/*
	 * clear out tuple table slots
	 */
	if (node->ss.ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->ss.ss_ScanTupleSlot);

	/*
	 * close down subplans
	 */
	ExecEndNode(outerPlanState(node));

	/*
	 * release bitmaps and buffers if any
	 */
	if (node->tbmiterator)
		tbm_end_iterate(node->tbmiterator);
	if (node->prefetch_iterator)
		tbm_end_iterate(node->prefetch_iterator);
	if (node->tbm)
		tbm_free(node->tbm);
	if (node->shared_tbmiterator)
		tbm_end_shared_iterate(node->shared_tbmiterator);
	if (node->shared_prefetch_iterator)
		tbm_end_shared_iterate(node->shared_prefetch_iterator);
	if (node->vmbuffer != InvalidBuffer)
		ReleaseBuffer(node->vmbuffer);
	if (node->pvmbuffer != InvalidBuffer)
		ReleaseBuffer(node->pvmbuffer);

	/*
	 * close heap scan
	 */
	table_endscan(scanDesc);
}