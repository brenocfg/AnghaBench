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
struct ct_timer {int irq_handling; int /*<<< orphan*/  lock; scalar_t__ reprogram; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_xfitimer_check_period (struct ct_timer*) ; 
 int ct_xfitimer_reprogram (struct ct_timer*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_xfitimer_callback(struct ct_timer *atimer)
{
	int update;
	unsigned long flags;

	spin_lock_irqsave(&atimer->lock, flags);
	atimer->irq_handling = 1;
	do {
		update = ct_xfitimer_reprogram(atimer, 1);
		spin_unlock(&atimer->lock);
		if (update)
			ct_xfitimer_check_period(atimer);
		spin_lock(&atimer->lock);
	} while (atimer->reprogram);
	atimer->irq_handling = 0;
	spin_unlock_irqrestore(&atimer->lock, flags);
}