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
struct ct_timer_instance {int running; int /*<<< orphan*/  running_list; scalar_t__ need_update; struct ct_timer* timer_base; } ;
struct ct_timer {int /*<<< orphan*/  lock; int /*<<< orphan*/  running_head; int /*<<< orphan*/  wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ct_xfitimer_get_wc (struct ct_timer*) ; 
 int /*<<< orphan*/  ct_xfitimer_update (struct ct_timer*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ct_xfitimer_start(struct ct_timer_instance *ti)
{
	struct ct_timer *atimer = ti->timer_base;
	unsigned long flags;

	spin_lock_irqsave(&atimer->lock, flags);
	if (list_empty(&ti->running_list))
		atimer->wc = ct_xfitimer_get_wc(atimer);
	ti->running = 1;
	ti->need_update = 0;
	list_add(&ti->running_list, &atimer->running_head);
	spin_unlock_irqrestore(&atimer->lock, flags);
	ct_xfitimer_update(atimer);
}