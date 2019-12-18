#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* plan; } ;
struct TYPE_15__ {int /*<<< orphan*/  choose_next_subplan; TYPE_4__* as_pstate; TYPE_1__ ps; int /*<<< orphan*/  pstate_len; } ;
struct TYPE_14__ {int /*<<< orphan*/  pa_lock; } ;
struct TYPE_13__ {int /*<<< orphan*/  toc; } ;
struct TYPE_12__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_3__ ParallelContext ;
typedef  TYPE_4__ ParallelAppendState ;
typedef  TYPE_5__ AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  LWLockInitialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWTRANCHE_PARALLEL_APPEND ; 
 int /*<<< orphan*/  choose_next_subplan_for_leader ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* shm_toc_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

void
ExecAppendInitializeDSM(AppendState *node,
						ParallelContext *pcxt)
{
	ParallelAppendState *pstate;

	pstate = shm_toc_allocate(pcxt->toc, node->pstate_len);
	memset(pstate, 0, node->pstate_len);
	LWLockInitialize(&pstate->pa_lock, LWTRANCHE_PARALLEL_APPEND);
	shm_toc_insert(pcxt->toc, node->ps.plan->plan_node_id, pstate);

	node->as_pstate = pstate;
	node->choose_next_subplan = choose_next_subplan_for_leader;
}