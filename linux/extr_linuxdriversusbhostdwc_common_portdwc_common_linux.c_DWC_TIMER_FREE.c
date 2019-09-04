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
struct TYPE_4__ {struct TYPE_4__* name; int /*<<< orphan*/  lock; scalar_t__ scheduled; int /*<<< orphan*/  t; } ;
typedef  TYPE_1__ dwc_timer_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

void DWC_TIMER_FREE(dwc_timer_t *timer)
{
	dwc_irqflags_t flags;

	DWC_SPINLOCK_IRQSAVE(timer->lock, &flags);

	if (timer->scheduled) {
		del_timer(&timer->t);
		timer->scheduled = 0;
	}

	DWC_SPINUNLOCK_IRQRESTORE(timer->lock, flags);
	DWC_SPINLOCK_FREE(timer->lock);
	DWC_FREE(timer->name);
	DWC_FREE(timer);
}