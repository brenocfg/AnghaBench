#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ biss_RuntimeContext; scalar_t__ biss_ScanDesc; scalar_t__ biss_RelationDesc; } ;
typedef  scalar_t__ Relation ;
typedef  scalar_t__ IndexScanDesc ;
typedef  TYPE_1__ BitmapIndexScanState ;

/* Variables and functions */
 int /*<<< orphan*/  FreeExprContext (scalar_t__,int) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  index_close (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_endscan (scalar_t__) ; 

void
ExecEndBitmapIndexScan(BitmapIndexScanState *node)
{
	Relation	indexRelationDesc;
	IndexScanDesc indexScanDesc;

	/*
	 * extract information from the node
	 */
	indexRelationDesc = node->biss_RelationDesc;
	indexScanDesc = node->biss_ScanDesc;

	/*
	 * Free the exprcontext ... now dead code, see ExecFreeExprContext
	 */
#ifdef NOT_USED
	if (node->biss_RuntimeContext)
		FreeExprContext(node->biss_RuntimeContext, true);
#endif

	/*
	 * close the index relation (no-op if we didn't open it)
	 */
	if (indexScanDesc)
		index_endscan(indexScanDesc);
	if (indexRelationDesc)
		index_close(indexRelationDesc, NoLock);
}