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
struct TYPE_3__ {scalar_t__ ioss_NumRuntimeKeys; int ioss_RuntimeKeysReady; int /*<<< orphan*/  ss; int /*<<< orphan*/  ioss_NumOrderByKeys; int /*<<< orphan*/  ioss_OrderByKeys; int /*<<< orphan*/  ioss_NumScanKeys; int /*<<< orphan*/  ioss_ScanKeys; scalar_t__ ioss_ScanDesc; int /*<<< orphan*/  ioss_RuntimeKeys; int /*<<< orphan*/ * ioss_RuntimeContext; } ;
typedef  TYPE_1__ IndexOnlyScanState ;
typedef  int /*<<< orphan*/  ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  ExecIndexEvalRuntimeKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ExecScanReScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_rescan (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecReScanIndexOnlyScan(IndexOnlyScanState *node)
{
	/*
	 * If we are doing runtime key calculations (ie, any of the index key
	 * values weren't simple Consts), compute the new key values.  But first,
	 * reset the context so we don't leak memory as each outer tuple is
	 * scanned.  Note this assumes that we will recalculate *all* runtime keys
	 * on each call.
	 */
	if (node->ioss_NumRuntimeKeys != 0)
	{
		ExprContext *econtext = node->ioss_RuntimeContext;

		ResetExprContext(econtext);
		ExecIndexEvalRuntimeKeys(econtext,
								 node->ioss_RuntimeKeys,
								 node->ioss_NumRuntimeKeys);
	}
	node->ioss_RuntimeKeysReady = true;

	/* reset index scan */
	if (node->ioss_ScanDesc)
		index_rescan(node->ioss_ScanDesc,
					 node->ioss_ScanKeys, node->ioss_NumScanKeys,
					 node->ioss_OrderByKeys, node->ioss_NumOrderByKeys);

	ExecScanReScan(&node->ss);
}