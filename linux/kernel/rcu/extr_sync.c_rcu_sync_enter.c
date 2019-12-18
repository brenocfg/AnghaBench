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
struct rcu_sync {int gp_state; int /*<<< orphan*/  gp_wait; int /*<<< orphan*/  cb_head; int /*<<< orphan*/  rss_lock; int /*<<< orphan*/  gp_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP_ENTER ; 
 int GP_IDLE ; 
 scalar_t__ GP_PASSED ; 
 scalar_t__ READ_ONCE (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_sync_func (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void rcu_sync_enter(struct rcu_sync *rsp)
{
	int gp_state;

	spin_lock_irq(&rsp->rss_lock);
	gp_state = rsp->gp_state;
	if (gp_state == GP_IDLE) {
		WRITE_ONCE(rsp->gp_state, GP_ENTER);
		WARN_ON_ONCE(rsp->gp_count);
		/*
		 * Note that we could simply do rcu_sync_call(rsp) here and
		 * avoid the "if (gp_state == GP_IDLE)" block below.
		 *
		 * However, synchronize_rcu() can be faster if rcu_expedited
		 * or rcu_blocking_is_gp() is true.
		 *
		 * Another reason is that we can't wait for rcu callback if
		 * we are called at early boot time but this shouldn't happen.
		 */
	}
	rsp->gp_count++;
	spin_unlock_irq(&rsp->rss_lock);

	if (gp_state == GP_IDLE) {
		/*
		 * See the comment above, this simply does the "synchronous"
		 * call_rcu(rcu_sync_func) which does GP_ENTER -> GP_PASSED.
		 */
		synchronize_rcu();
		rcu_sync_func(&rsp->cb_head);
		/* Not really needed, wait_event() would see GP_PASSED. */
		return;
	}

	wait_event(rsp->gp_wait, READ_ONCE(rsp->gp_state) >= GP_PASSED);
}