#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int prefetch_target; int prefetch_maximum; TYPE_1__* pstate; } ;
struct TYPE_4__ {int prefetch_target; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ ParallelBitmapHeapState ;
typedef  TYPE_2__ BitmapHeapScanState ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
BitmapAdjustPrefetchTarget(BitmapHeapScanState *node)
{
#ifdef USE_PREFETCH
	ParallelBitmapHeapState *pstate = node->pstate;

	if (pstate == NULL)
	{
		if (node->prefetch_target >= node->prefetch_maximum)
			 /* don't increase any further */ ;
		else if (node->prefetch_target >= node->prefetch_maximum / 2)
			node->prefetch_target = node->prefetch_maximum;
		else if (node->prefetch_target > 0)
			node->prefetch_target *= 2;
		else
			node->prefetch_target++;
		return;
	}

	/* Do an unlocked check first to save spinlock acquisitions. */
	if (pstate->prefetch_target < node->prefetch_maximum)
	{
		SpinLockAcquire(&pstate->mutex);
		if (pstate->prefetch_target >= node->prefetch_maximum)
			 /* don't increase any further */ ;
		else if (pstate->prefetch_target >= node->prefetch_maximum / 2)
			pstate->prefetch_target = node->prefetch_maximum;
		else if (pstate->prefetch_target > 0)
			pstate->prefetch_target *= 2;
		else
			pstate->prefetch_target++;
		SpinLockRelease(&pstate->mutex);
	}
#endif							/* USE_PREFETCH */
}