#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* name; int /*<<< orphan*/  data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ) ;scalar_t__ hz; } ;
typedef  TYPE_1__ work_container_t ;
struct work {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; TYPE_1__* container; } ;
typedef  TYPE_2__ dwc_workq_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DEBUG (char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_WAITQ_TRIGGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsleep (TYPE_1__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void do_work(struct work *task, void *data)
{
	dwc_workq_t *wq = (dwc_workq_t *)data;
	work_container_t *container = wq->container;
	dwc_irqflags_t flags;

	if (container->hz) {
		tsleep(container, 0, "dw3wrk", container->hz);
	}

	container->cb(container->data);
	DWC_DEBUG("Work done: %s, container=%p", container->name, container);

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);
	if (container->name)
		DWC_FREE(container->name);
	DWC_FREE(container);
	wq->pending--;
	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
	DWC_WAITQ_TRIGGER(wq->waitq);
}