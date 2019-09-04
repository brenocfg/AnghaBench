#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; scalar_t__ pending; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_ALLOC () ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_ALLOC () ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

dwc_workq_t *DWC_WORKQ_ALLOC(char *name)
{
	dwc_workq_t *wq = DWC_ALLOC(sizeof(*wq));

	if (!wq) {
		return NULL;
	}

	wq->wq = create_singlethread_workqueue(name);
	if (!wq->wq) {
		goto no_wq;
	}

	wq->pending = 0;

#if (defined(DWC_LINUX) && defined(CONFIG_DEBUG_SPINLOCK))
	DWC_SPINLOCK_ALLOC_LINUX_DEBUG(wq->lock);
#else
	wq->lock = DWC_SPINLOCK_ALLOC();
#endif
	if (!wq->lock) {
		goto no_lock;
	}

	wq->waitq = DWC_WAITQ_ALLOC();
	if (!wq->waitq) {
		goto no_waitq;
	}

#ifdef DEBUG
	DWC_CIRCLEQ_INIT(&wq->entries);
#endif
	return wq;

 no_waitq:
	DWC_SPINLOCK_FREE(wq->lock);
 no_lock:
	destroy_workqueue(wq->wq);
 no_wq:
	DWC_FREE(wq);

	return NULL;
}