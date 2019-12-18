#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* plan; TYPE_1__* state; } ;
struct TYPE_14__ {int /*<<< orphan*/  ss_currentScanDesc; TYPE_3__ ps; } ;
struct TYPE_17__ {TYPE_4__ ss; TYPE_6__* pstate; } ;
struct TYPE_16__ {int /*<<< orphan*/  phs_snapshot_data; } ;
struct TYPE_15__ {int /*<<< orphan*/  toc; } ;
struct TYPE_12__ {int /*<<< orphan*/  plan_node_id; } ;
struct TYPE_11__ {int /*<<< orphan*/ * es_query_dsa; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_5__ ParallelWorkerContext ;
typedef  TYPE_6__ ParallelBitmapHeapState ;
typedef  TYPE_7__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RestoreSnapshot (int /*<<< orphan*/ ) ; 
 TYPE_6__* shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table_scan_update_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ExecBitmapHeapInitializeWorker(BitmapHeapScanState *node,
							   ParallelWorkerContext *pwcxt)
{
	ParallelBitmapHeapState *pstate;
	Snapshot	snapshot;

	Assert(node->ss.ps.state->es_query_dsa != NULL);

	pstate = shm_toc_lookup(pwcxt->toc, node->ss.ps.plan->plan_node_id, false);
	node->pstate = pstate;

	snapshot = RestoreSnapshot(pstate->phs_snapshot_data);
	table_scan_update_snapshot(node->ss.ss_currentScanDesc, snapshot);
}