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
struct TYPE_4__ {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  wq; } ;
typedef  TYPE_1__ dwc_workq_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

void DWC_WORKQ_FREE(dwc_workq_t *wq)
{
#ifdef DEBUG
	if (wq->pending != 0) {
		struct work_container *wc;
		DWC_ERROR("Destroying work queue with pending work");
		DWC_CIRCLEQ_FOREACH(wc, &wq->entries, entry) {
			DWC_ERROR("Work %s still pending", wc->name);
		}
	}
#endif
	destroy_workqueue(wq->wq);
	DWC_SPINLOCK_FREE(wq->lock);
	DWC_WAITQ_FREE(wq->waitq);
	DWC_FREE(wq);
}