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
struct ct_timer_instance {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_systimer_stop(struct ct_timer_instance *ti)
{
	unsigned long flags;

	spin_lock_irqsave(&ti->lock, flags);
	ti->running = 0;
	del_timer(&ti->timer);
	spin_unlock_irqrestore(&ti->lock, flags);
}