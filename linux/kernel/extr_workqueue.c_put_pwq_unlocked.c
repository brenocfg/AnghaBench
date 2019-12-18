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
struct pool_workqueue {TYPE_1__* pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_pwq (struct pool_workqueue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_pwq_unlocked(struct pool_workqueue *pwq)
{
	if (pwq) {
		/*
		 * As both pwqs and pools are RCU protected, the
		 * following lock operations are safe.
		 */
		spin_lock_irq(&pwq->pool->lock);
		put_pwq(pwq);
		spin_unlock_irq(&pwq->pool->lock);
	}
}