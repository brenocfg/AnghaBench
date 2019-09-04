#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct b43_wldev {TYPE_1__* wl; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  hardirq_lock; } ;

/* Variables and functions */
 scalar_t__ B43_STAT_STARTED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  b43_do_interrupt (struct b43_wldev*) ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t b43_interrupt_handler(int irq, void *dev_id)
{
	struct b43_wldev *dev = dev_id;
	irqreturn_t ret;

	if (unlikely(b43_status(dev) < B43_STAT_STARTED))
		return IRQ_NONE;

	spin_lock(&dev->wl->hardirq_lock);
	ret = b43_do_interrupt(dev);
	mmiowb();
	spin_unlock(&dev->wl->hardirq_lock);

	return ret;
}