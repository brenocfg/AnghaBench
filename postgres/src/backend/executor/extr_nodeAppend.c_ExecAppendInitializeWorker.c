#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* plan; } ;
struct TYPE_10__ {int /*<<< orphan*/  choose_next_subplan; TYPE_2__ ps; int /*<<< orphan*/  as_pstate; } ;
struct TYPE_9__ {int /*<<< orphan*/  toc; } ;
struct TYPE_7__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_3__ ParallelWorkerContext ;
typedef  TYPE_4__ AppendState ;

/* Variables and functions */
 int /*<<< orphan*/  choose_next_subplan_for_worker ; 
 int /*<<< orphan*/  shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ExecAppendInitializeWorker(AppendState *node, ParallelWorkerContext *pwcxt)
{
	node->as_pstate = shm_toc_lookup(pwcxt->toc, node->ps.plan->plan_node_id, false);
	node->choose_next_subplan = choose_next_subplan_for_worker;
}