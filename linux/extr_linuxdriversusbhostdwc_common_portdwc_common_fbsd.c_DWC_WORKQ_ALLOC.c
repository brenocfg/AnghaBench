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
struct TYPE_5__ {int /*<<< orphan*/  taskq; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; scalar_t__ pending; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 TYPE_1__* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_ALLOC () ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_ALLOC () ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PWAIT ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

dwc_workq_t *DWC_WORKQ_ALLOC(char *name)
{
	dwc_workq_t *wq = DWC_ALLOC(sizeof(*wq));

	if (!wq) {
		DWC_ERROR("Cannot allocate memory for workqueue");
		return NULL;
	}

	wq->taskq = taskqueue_create(name, M_NOWAIT, taskqueue_thread_enqueue, &wq->taskq);
	if (!wq->taskq) {
		DWC_ERROR("Cannot allocate memory for taskqueue");
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

	taskqueue_start_threads(&wq->taskq, 1, PWAIT, "%s taskq", "dw3tsk");

#ifdef DEBUG
	DWC_CIRCLEQ_INIT(&wq->entries);
#endif
	return wq;

 no_waitq:
	DWC_SPINLOCK_FREE(wq->lock);
 no_lock:
	taskqueue_free(wq->taskq);
 no_taskq:
	DWC_FREE(wq);

	return NULL;
}