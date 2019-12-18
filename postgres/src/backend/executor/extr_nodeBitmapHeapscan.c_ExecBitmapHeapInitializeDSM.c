#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_13__ {TYPE_1__* plan; TYPE_6__* state; } ;
struct TYPE_14__ {TYPE_2__ ps; } ;
struct TYPE_18__ {TYPE_5__* pstate; TYPE_3__ ss; int /*<<< orphan*/  pscan_len; } ;
struct TYPE_17__ {int /*<<< orphan*/  es_snapshot; int /*<<< orphan*/ * es_query_dsa; } ;
struct TYPE_16__ {int /*<<< orphan*/  phs_snapshot_data; int /*<<< orphan*/  cv; int /*<<< orphan*/  state; scalar_t__ prefetch_target; scalar_t__ prefetch_pages; int /*<<< orphan*/  mutex; scalar_t__ prefetch_iterator; scalar_t__ tbmiterator; } ;
struct TYPE_15__ {int /*<<< orphan*/  toc; } ;
struct TYPE_12__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_4__ ParallelContext ;
typedef  TYPE_5__ ParallelBitmapHeapState ;
typedef  TYPE_6__ EState ;
typedef  TYPE_7__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  BM_INITIAL ; 
 int /*<<< orphan*/  ConditionVariableInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SerializeSnapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 TYPE_5__* shm_toc_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

void
ExecBitmapHeapInitializeDSM(BitmapHeapScanState *node,
							ParallelContext *pcxt)
{
	ParallelBitmapHeapState *pstate;
	EState	   *estate = node->ss.ps.state;
	dsa_area   *dsa = node->ss.ps.state->es_query_dsa;

	/* If there's no DSA, there are no workers; initialize nothing. */
	if (dsa == NULL)
		return;

	pstate = shm_toc_allocate(pcxt->toc, node->pscan_len);

	pstate->tbmiterator = 0;
	pstate->prefetch_iterator = 0;

	/* Initialize the mutex */
	SpinLockInit(&pstate->mutex);
	pstate->prefetch_pages = 0;
	pstate->prefetch_target = 0;
	pstate->state = BM_INITIAL;

	ConditionVariableInit(&pstate->cv);
	SerializeSnapshot(estate->es_snapshot, pstate->phs_snapshot_data);

	shm_toc_insert(pcxt->toc, node->ss.ps.plan->plan_node_id, pstate);
	node->pstate = pstate;
}