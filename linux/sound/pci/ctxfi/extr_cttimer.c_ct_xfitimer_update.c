#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ct_timer {int reprogram; int /*<<< orphan*/  lock; scalar_t__ irq_handling; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_xfitimer_irq_stop (struct ct_timer*) ; 
 int /*<<< orphan*/  ct_xfitimer_reprogram (struct ct_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_xfitimer_update(struct ct_timer *atimer)
{
	unsigned long flags;

	spin_lock_irqsave(&atimer->lock, flags);
	if (atimer->irq_handling) {
		/* reached from IRQ handler; let it handle later */
		atimer->reprogram = 1;
		spin_unlock_irqrestore(&atimer->lock, flags);
		return;
	}

	ct_xfitimer_irq_stop(atimer);
	ct_xfitimer_reprogram(atimer, 0);
	spin_unlock_irqrestore(&atimer->lock, flags);
}