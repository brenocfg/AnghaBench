#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  taskq; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ ) ; 

void DWC_WORKQ_FREE(dwc_workq_t *wq)
{
#ifdef DEBUG
	dwc_irqflags_t flags;

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);

	if (wq->pending != 0) {
		struct work_container *container;

		DWC_ERROR("Destroying work queue with pending work");

		DWC_CIRCLEQ_FOREACH(container, &wq->entries, entry) {
			DWC_ERROR("Work %s still pending", container->name);
		}
	}

	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
#endif
	DWC_WAITQ_FREE(wq->waitq);
	DWC_SPINLOCK_FREE(wq->lock);
	taskqueue_free(wq->taskq);
	DWC_FREE(wq);
}