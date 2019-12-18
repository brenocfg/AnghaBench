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
struct TYPE_3__ {int biss_RuntimeKeysReady; int /*<<< orphan*/  biss_NumScanKeys; int /*<<< orphan*/  biss_ScanKeys; int /*<<< orphan*/  biss_ScanDesc; int /*<<< orphan*/  biss_NumArrayKeys; int /*<<< orphan*/  biss_ArrayKeys; int /*<<< orphan*/  biss_NumRuntimeKeys; int /*<<< orphan*/  biss_RuntimeKeys; int /*<<< orphan*/ * biss_RuntimeContext; } ;
typedef  int /*<<< orphan*/  ExprContext ;
typedef  TYPE_1__ BitmapIndexScanState ;

/* Variables and functions */
 int ExecIndexEvalArrayKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExecIndexEvalRuntimeKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetExprContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_rescan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ExecReScanBitmapIndexScan(BitmapIndexScanState *node)
{
	ExprContext *econtext = node->biss_RuntimeContext;

	/*
	 * Reset the runtime-key context so we don't leak memory as each outer
	 * tuple is scanned.  Note this assumes that we will recalculate *all*
	 * runtime keys on each call.
	 */
	if (econtext)
		ResetExprContext(econtext);

	/*
	 * If we are doing runtime key calculations (ie, any of the index key
	 * values weren't simple Consts), compute the new key values.
	 *
	 * Array keys are also treated as runtime keys; note that if we return
	 * with biss_RuntimeKeysReady still false, then there is an empty array
	 * key so no index scan is needed.
	 */
	if (node->biss_NumRuntimeKeys != 0)
		ExecIndexEvalRuntimeKeys(econtext,
								 node->biss_RuntimeKeys,
								 node->biss_NumRuntimeKeys);
	if (node->biss_NumArrayKeys != 0)
		node->biss_RuntimeKeysReady =
			ExecIndexEvalArrayKeys(econtext,
								   node->biss_ArrayKeys,
								   node->biss_NumArrayKeys);
	else
		node->biss_RuntimeKeysReady = true;

	/* reset index scan */
	if (node->biss_RuntimeKeysReady)
		index_rescan(node->biss_ScanDesc,
					 node->biss_ScanKeys, node->biss_NumScanKeys,
					 NULL, 0);
}