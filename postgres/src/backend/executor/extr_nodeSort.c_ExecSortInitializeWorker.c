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
struct TYPE_12__ {int /*<<< orphan*/  toc; } ;
struct TYPE_9__ {TYPE_1__* plan; } ;
struct TYPE_10__ {TYPE_2__ ps; } ;
struct TYPE_11__ {int am_worker; TYPE_3__ ss; int /*<<< orphan*/  shared_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_4__ SortState ;
typedef  TYPE_5__ ParallelWorkerContext ;

/* Variables and functions */
 int /*<<< orphan*/  shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ExecSortInitializeWorker(SortState *node, ParallelWorkerContext *pwcxt)
{
	node->shared_info =
		shm_toc_lookup(pwcxt->toc, node->ss.ps.plan->plan_node_id, true);
	node->am_worker = true;
}