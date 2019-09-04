#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct TYPE_5__ {int scheduled; int /*<<< orphan*/  lock; TYPE_2__ t; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ dwc_timer_t ;
typedef  int /*<<< orphan*/  dwc_irqflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DEBUGC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_IRQSAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_SPINUNLOCK_IRQRESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void DWC_TIMER_SCHEDULE(dwc_timer_t *timer, uint32_t time)
{
	dwc_irqflags_t flags;

	DWC_SPINLOCK_IRQSAVE(timer->lock, &flags);

	if (!timer->scheduled) {
		timer->scheduled = 1;
		DWC_DEBUGC("Scheduling timer %s to expire in +%d msec", timer->name, time);
		timer->t.expires = jiffies + msecs_to_jiffies(time);
		add_timer(&timer->t);
	} else {
		DWC_DEBUGC("Modifying timer %s to expire in +%d msec", timer->name, time);
		mod_timer(&timer->t, jiffies + msecs_to_jiffies(time));
	}

	DWC_SPINUNLOCK_IRQRESTORE(timer->lock, flags);
}