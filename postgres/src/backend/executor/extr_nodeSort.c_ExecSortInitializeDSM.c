#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TuplesortInstrumentation ;
struct TYPE_16__ {int num_workers; } ;
struct TYPE_15__ {int nworkers; int /*<<< orphan*/  toc; } ;
struct TYPE_13__ {TYPE_1__* plan; int /*<<< orphan*/  instrument; } ;
struct TYPE_12__ {TYPE_3__ ps; } ;
struct TYPE_14__ {TYPE_6__* shared_info; TYPE_2__ ss; } ;
struct TYPE_11__ {int /*<<< orphan*/  plan_node_id; } ;
typedef  TYPE_4__ SortState ;
typedef  scalar_t__ Size ;
typedef  TYPE_5__ ParallelContext ;

/* Variables and functions */
 int /*<<< orphan*/  SharedSortInfo ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* shm_toc_allocate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  sinstrument ; 

void
ExecSortInitializeDSM(SortState *node, ParallelContext *pcxt)
{
	Size		size;

	/* don't need this if not instrumenting or no workers */
	if (!node->ss.ps.instrument || pcxt->nworkers == 0)
		return;

	size = offsetof(SharedSortInfo, sinstrument)
		+ pcxt->nworkers * sizeof(TuplesortInstrumentation);
	node->shared_info = shm_toc_allocate(pcxt->toc, size);
	/* ensure any unfilled slots will contain zeroes */
	memset(node->shared_info, 0, size);
	node->shared_info->num_workers = pcxt->nworkers;
	shm_toc_insert(pcxt->toc, node->ss.ps.plan->plan_node_id,
				   node->shared_info);
}