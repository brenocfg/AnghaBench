#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ iss_NumRuntimeKeys; int iss_RuntimeKeysReady; int iss_ReachedEnd; int /*<<< orphan*/  ss; int /*<<< orphan*/  iss_NumOrderByKeys; int /*<<< orphan*/  iss_OrderByKeys; int /*<<< orphan*/  iss_NumScanKeys; int /*<<< orphan*/  iss_ScanKeys; scalar_t__ iss_ScanDesc; scalar_t__ iss_ReorderQueue; int /*<<< orphan*/  iss_RuntimeKeys; int /*<<< orphan*/ * iss_RuntimeContext; } ;
typedef  TYPE_1__ IndexScanState ;
typedef  int /*<<< orphan*/  ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecIndexEvalRuntimeKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ExecScanReScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_rescan (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pairingheap_is_empty (scalar_t__) ; 
 int /*<<< orphan*/  reorderqueue_pop (TYPE_1__*) ; 

void
ExecReScanIndexScan(IndexScanState *node)
{
	/*
	 * If we are doing runtime key calculations (ie, any of the index key
	 * values weren't simple Consts), compute the new key values.  But first,
	 * reset the context so we don't leak memory as each outer tuple is
	 * scanned.  Note this assumes that we will recalculate *all* runtime keys
	 * on each call.
	 */
	if (node->iss_NumRuntimeKeys != 0)
	{
		ExprContext *econtext = node->iss_RuntimeContext;

		ResetExprContext(econtext);
		ExecIndexEvalRuntimeKeys(econtext,
								 node->iss_RuntimeKeys,
								 node->iss_NumRuntimeKeys);
	}
	node->iss_RuntimeKeysReady = true;

	/* flush the reorder queue */
	if (node->iss_ReorderQueue)
	{
		while (!pairingheap_is_empty(node->iss_ReorderQueue))
			reorderqueue_pop(node);
	}

	/* reset index scan */
	if (node->iss_ScanDesc)
		index_rescan(node->iss_ScanDesc,
					 node->iss_ScanKeys, node->iss_NumScanKeys,
					 node->iss_OrderByKeys, node->iss_NumOrderByKeys);
	node->iss_ReachedEnd = false;

	ExecScanReScan(&node->ss);
}