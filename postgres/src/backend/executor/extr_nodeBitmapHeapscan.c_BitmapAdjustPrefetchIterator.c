#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ prefetch_pages; scalar_t__ prefetch_maximum; int /*<<< orphan*/ * shared_prefetch_iterator; int /*<<< orphan*/ * prefetch_iterator; TYPE_2__* pstate; } ;
struct TYPE_8__ {scalar_t__ prefetch_pages; int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {scalar_t__ blockno; } ;
typedef  int /*<<< orphan*/  TBMSharedIterator ;
typedef  int /*<<< orphan*/  TBMIterator ;
typedef  TYPE_1__ TBMIterateResult ;
typedef  TYPE_2__ ParallelBitmapHeapState ;
typedef  TYPE_3__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* tbm_iterate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_shared_iterate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
BitmapAdjustPrefetchIterator(BitmapHeapScanState *node,
							 TBMIterateResult *tbmres)
{
#ifdef USE_PREFETCH
	ParallelBitmapHeapState *pstate = node->pstate;

	if (pstate == NULL)
	{
		TBMIterator *prefetch_iterator = node->prefetch_iterator;

		if (node->prefetch_pages > 0)
		{
			/* The main iterator has closed the distance by one page */
			node->prefetch_pages--;
		}
		else if (prefetch_iterator)
		{
			/* Do not let the prefetch iterator get behind the main one */
			TBMIterateResult *tbmpre = tbm_iterate(prefetch_iterator);

			if (tbmpre == NULL || tbmpre->blockno != tbmres->blockno)
				elog(ERROR, "prefetch and main iterators are out of sync");
		}
		return;
	}

	if (node->prefetch_maximum > 0)
	{
		TBMSharedIterator *prefetch_iterator = node->shared_prefetch_iterator;

		SpinLockAcquire(&pstate->mutex);
		if (pstate->prefetch_pages > 0)
		{
			pstate->prefetch_pages--;
			SpinLockRelease(&pstate->mutex);
		}
		else
		{
			/* Release the mutex before iterating */
			SpinLockRelease(&pstate->mutex);

			/*
			 * In case of shared mode, we can not ensure that the current
			 * blockno of the main iterator and that of the prefetch iterator
			 * are same.  It's possible that whatever blockno we are
			 * prefetching will be processed by another process.  Therefore,
			 * we don't validate the blockno here as we do in non-parallel
			 * case.
			 */
			if (prefetch_iterator)
				tbm_shared_iterate(prefetch_iterator);
		}
	}
#endif							/* USE_PREFETCH */
}