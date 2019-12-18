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
struct TYPE_7__ {scalar_t__ ps_ResultTupleSlot; } ;
struct TYPE_5__ {scalar_t__ ss_ScanTupleSlot; TYPE_3__ ps; } ;
struct TYPE_6__ {TYPE_1__ ss; scalar_t__ iss_RuntimeContext; scalar_t__ iss_ScanDesc; scalar_t__ iss_RelationDesc; } ;
typedef  scalar_t__ Relation ;
typedef  TYPE_2__ IndexScanState ;
typedef  scalar_t__ IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  ExecClearTuple (scalar_t__) ; 
 int /*<<< orphan*/  ExecFreeExprContext (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeExprContext (scalar_t__,int) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  index_close (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_endscan (scalar_t__) ; 

void
ExecEndIndexScan(IndexScanState *node)
{
	Relation	indexRelationDesc;
	IndexScanDesc indexScanDesc;

	/*
	 * extract information from the node
	 */
	indexRelationDesc = node->iss_RelationDesc;
	indexScanDesc = node->iss_ScanDesc;

	/*
	 * Free the exprcontext(s) ... now dead code, see ExecFreeExprContext
	 */
#ifdef NOT_USED
	ExecFreeExprContext(&node->ss.ps);
	if (node->iss_RuntimeContext)
		FreeExprContext(node->iss_RuntimeContext, true);
#endif

	/*
	 * clear out tuple table slots
	 */
	if (node->ss.ps.ps_ResultTupleSlot)
		ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->ss.ss_ScanTupleSlot);

	/*
	 * close the index relation (no-op if we didn't open it)
	 */
	if (indexScanDesc)
		index_endscan(indexScanDesc);
	if (indexRelationDesc)
		index_close(indexRelationDesc, NoLock);
}