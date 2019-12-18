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
struct ct_timer_instance {int /*<<< orphan*/  instance_list; struct ct_timer* timer_base; } ;
struct ct_timer {int /*<<< orphan*/  list_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_instance ) (struct ct_timer_instance*) ;int /*<<< orphan*/  (* stop ) (struct ct_timer_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ct_timer_instance*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ct_timer_instance*) ; 
 int /*<<< orphan*/  stub2 (struct ct_timer_instance*) ; 

void ct_timer_instance_free(struct ct_timer_instance *ti)
{
	struct ct_timer *atimer = ti->timer_base;

	atimer->ops->stop(ti); /* to be sure */
	if (atimer->ops->free_instance)
		atimer->ops->free_instance(ti);

	spin_lock_irq(&atimer->list_lock);
	list_del(&ti->instance_list);
	spin_unlock_irq(&atimer->list_lock);

	kfree(ti);
}