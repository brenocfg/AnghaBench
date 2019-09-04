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
struct ct_timer_instance {scalar_t__ running; int /*<<< orphan*/  running_list; struct ct_timer* timer_base; } ;
struct ct_timer {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_xfitimer_update (struct ct_timer*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_xfitimer_stop(struct ct_timer_instance *ti)
{
	struct ct_timer *atimer = ti->timer_base;
	unsigned long flags;

	spin_lock_irqsave(&atimer->lock, flags);
	list_del_init(&ti->running_list);
	ti->running = 0;
	spin_unlock_irqrestore(&atimer->lock, flags);
	ct_xfitimer_update(atimer);
}