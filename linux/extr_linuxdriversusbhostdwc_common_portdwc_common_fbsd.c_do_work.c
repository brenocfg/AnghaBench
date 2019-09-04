#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* name; int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;scalar_t__ hz; TYPE_2__* wq; } ;
typedef  TYPE_1__ work_container_t ;
struct TYPE_7__ {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; } ;
typedef  TYPE_2__ dwc_workq_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DEBUG (char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_TRIGGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_work(void *data, int pending)	// what to do with pending ???
{
	work_container_t *container = (work_container_t *)data;
	dwc_workq_t *wq = container->wq;
	dwc_irqflags_t flags;

	if (container->hz) {
		pause("dw3wrk", container->hz);
	}

	container->cb(container->data);
	DWC_DEBUG("Work done: %s, container=%p", container->name, container);

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);

#ifdef DEBUG
	DWC_CIRCLEQ_REMOVE(&wq->entries, container, entry);
#endif
	if (container->name)
		DWC_FREE(container->name);
	DWC_FREE(container);
	wq->pending--;
	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
	DWC_WAITQ_TRIGGER(wq->waitq);
}