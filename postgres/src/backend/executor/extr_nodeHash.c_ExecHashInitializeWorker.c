#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* plan; int /*<<< orphan*/  instrument; } ;
struct TYPE_12__ {int /*<<< orphan*/ * hinstrument; TYPE_2__ ps; } ;
struct TYPE_11__ {int /*<<< orphan*/  toc; } ;
struct TYPE_10__ {int /*<<< orphan*/ * hinstrument; } ;
struct TYPE_8__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_3__ SharedHashInfo ;
typedef  TYPE_4__ ParallelWorkerContext ;
typedef  TYPE_5__ HashState ;

/* Variables and functions */
 size_t ParallelWorkerNumber ; 
 scalar_t__ shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ExecHashInitializeWorker(HashState *node, ParallelWorkerContext *pwcxt)
{
	SharedHashInfo *shared_info;

	/* don't need this if not instrumenting */
	if (!node->ps.instrument)
		return;

	shared_info = (SharedHashInfo *)
		shm_toc_lookup(pwcxt->toc, node->ps.plan->plan_node_id, false);
	node->hinstrument = &shared_info->hinstrument[ParallelWorkerNumber];
}