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
struct rcu_sync {scalar_t__ gp_state; size_t gp_type; int /*<<< orphan*/  gp_wait; int /*<<< orphan*/  rss_lock; int /*<<< orphan*/  gp_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ GP_IDLE ; 
 scalar_t__ GP_PASSED ; 
 scalar_t__ GP_PENDING ; 
 TYPE_1__* gp_ops ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void rcu_sync_enter(struct rcu_sync *rsp)
{
	bool need_wait, need_sync;

	spin_lock_irq(&rsp->rss_lock);
	need_wait = rsp->gp_count++;
	need_sync = rsp->gp_state == GP_IDLE;
	if (need_sync)
		rsp->gp_state = GP_PENDING;
	spin_unlock_irq(&rsp->rss_lock);

	BUG_ON(need_wait && need_sync);

	if (need_sync) {
		gp_ops[rsp->gp_type].sync();
		rsp->gp_state = GP_PASSED;
		wake_up_all(&rsp->gp_wait);
	} else if (need_wait) {
		wait_event(rsp->gp_wait, rsp->gp_state == GP_PASSED);
	} else {
		/*
		 * Possible when there's a pending CB from a rcu_sync_exit().
		 * Nobody has yet been allowed the 'fast' path and thus we can
		 * avoid doing any sync(). The callback will get 'dropped'.
		 */
		BUG_ON(rsp->gp_state != GP_PASSED);
	}
}