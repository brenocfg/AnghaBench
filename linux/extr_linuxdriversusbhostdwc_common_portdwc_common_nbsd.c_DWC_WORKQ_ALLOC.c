#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  taskq; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; scalar_t__ pending; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_ALLOC () ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_ALLOC () ; 
 int /*<<< orphan*/  IPL_BIO ; 
 int /*<<< orphan*/  do_work ; 
 int workqueue_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workqueue_destroy (int /*<<< orphan*/ ) ; 

dwc_workq_t *DWC_WORKQ_ALLOC(char *name)
{
	int result;
	dwc_workq_t *wq = DWC_ALLOC(sizeof(*wq));

	if (!wq) {
		DWC_ERROR("Cannot allocate memory for workqueue");
		return NULL;
	}

	result = workqueue_create(&wq->taskq, name, do_work, wq, 0 /*PWAIT*/,
				  IPL_BIO, 0);
	if (result) {
		DWC_ERROR("Cannot create workqueue");
		goto no_taskq;
	}

	wq->pending = 0;

	wq->lock = DWC_SPINLOCK_ALLOC();
	if (!wq->lock) {
		DWC_ERROR("Cannot allocate memory for spinlock");
		goto no_lock;
	}

	wq->waitq = DWC_WAITQ_ALLOC();
	if (!wq->waitq) {
		DWC_ERROR("Cannot allocate memory for waitqueue");
		goto no_waitq;
	}

	return wq;

 no_waitq:
	DWC_SPINLOCK_FREE(wq->lock);
 no_lock:
	workqueue_destroy(wq->taskq);
 no_taskq:
	DWC_FREE(wq);

	return NULL;
}