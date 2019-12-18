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
typedef  TYPE_3__* TableScanDesc ;
struct TYPE_12__ {int /*<<< orphan*/  ss_currentRelation; } ;
struct TYPE_16__ {scalar_t__ prefetch_pages; scalar_t__ prefetch_target; int /*<<< orphan*/  pvmbuffer; TYPE_2__ ss; TYPE_1__* tbmres; scalar_t__ can_skip_fetch; int /*<<< orphan*/ * shared_prefetch_iterator; int /*<<< orphan*/ * prefetch_iterator; TYPE_5__* pstate; } ;
struct TYPE_15__ {scalar_t__ prefetch_pages; scalar_t__ prefetch_target; int /*<<< orphan*/  mutex; } ;
struct TYPE_14__ {int /*<<< orphan*/  blockno; } ;
struct TYPE_13__ {int /*<<< orphan*/  rs_rd; } ;
struct TYPE_11__ {int /*<<< orphan*/  recheck; } ;
typedef  int /*<<< orphan*/  TBMSharedIterator ;
typedef  int /*<<< orphan*/  TBMIterator ;
typedef  TYPE_4__ TBMIterateResult ;
typedef  TYPE_5__ ParallelBitmapHeapState ;
typedef  TYPE_6__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 int /*<<< orphan*/  PrefetchBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_ALL_VISIBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_end_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_end_shared_iterate (int /*<<< orphan*/ *) ; 
 TYPE_4__* tbm_iterate (int /*<<< orphan*/ *) ; 
 TYPE_4__* tbm_shared_iterate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
BitmapPrefetch(BitmapHeapScanState *node, TableScanDesc scan)
{
#ifdef USE_PREFETCH
	ParallelBitmapHeapState *pstate = node->pstate;

	if (pstate == NULL)
	{
		TBMIterator *prefetch_iterator = node->prefetch_iterator;

		if (prefetch_iterator)
		{
			while (node->prefetch_pages < node->prefetch_target)
			{
				TBMIterateResult *tbmpre = tbm_iterate(prefetch_iterator);
				bool		skip_fetch;

				if (tbmpre == NULL)
				{
					/* No more pages to prefetch */
					tbm_end_iterate(prefetch_iterator);
					node->prefetch_iterator = NULL;
					break;
				}
				node->prefetch_pages++;

				/*
				 * If we expect not to have to actually read this heap page,
				 * skip this prefetch call, but continue to run the prefetch
				 * logic normally.  (Would it be better not to increment
				 * prefetch_pages?)
				 *
				 * This depends on the assumption that the index AM will
				 * report the same recheck flag for this future heap page as
				 * it did for the current heap page; which is not a certainty
				 * but is true in many cases.
				 */
				skip_fetch = (node->can_skip_fetch &&
							  (node->tbmres ? !node->tbmres->recheck : false) &&
							  VM_ALL_VISIBLE(node->ss.ss_currentRelation,
											 tbmpre->blockno,
											 &node->pvmbuffer));

				if (!skip_fetch)
					PrefetchBuffer(scan->rs_rd, MAIN_FORKNUM, tbmpre->blockno);
			}
		}

		return;
	}

	if (pstate->prefetch_pages < pstate->prefetch_target)
	{
		TBMSharedIterator *prefetch_iterator = node->shared_prefetch_iterator;

		if (prefetch_iterator)
		{
			while (1)
			{
				TBMIterateResult *tbmpre;
				bool		do_prefetch = false;
				bool		skip_fetch;

				/*
				 * Recheck under the mutex. If some other process has already
				 * done enough prefetching then we need not to do anything.
				 */
				SpinLockAcquire(&pstate->mutex);
				if (pstate->prefetch_pages < pstate->prefetch_target)
				{
					pstate->prefetch_pages++;
					do_prefetch = true;
				}
				SpinLockRelease(&pstate->mutex);

				if (!do_prefetch)
					return;

				tbmpre = tbm_shared_iterate(prefetch_iterator);
				if (tbmpre == NULL)
				{
					/* No more pages to prefetch */
					tbm_end_shared_iterate(prefetch_iterator);
					node->shared_prefetch_iterator = NULL;
					break;
				}

				/* As above, skip prefetch if we expect not to need page */
				skip_fetch = (node->can_skip_fetch &&
							  (node->tbmres ? !node->tbmres->recheck : false) &&
							  VM_ALL_VISIBLE(node->ss.ss_currentRelation,
											 tbmpre->blockno,
											 &node->pvmbuffer));

				if (!skip_fetch)
					PrefetchBuffer(scan->rs_rd, MAIN_FORKNUM, tbmpre->blockno);
			}
		}
	}
#endif							/* USE_PREFETCH */
}