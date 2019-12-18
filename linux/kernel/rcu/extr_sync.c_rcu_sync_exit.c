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
struct rcu_sync {scalar_t__ gp_state; scalar_t__ gp_count; int /*<<< orphan*/  rss_lock; } ;

/* Variables and functions */
 scalar_t__ GP_EXIT ; 
 scalar_t__ GP_IDLE ; 
 scalar_t__ GP_PASSED ; 
 scalar_t__ GP_REPLAY ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rcu_sync_call (struct rcu_sync*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rcu_sync_exit(struct rcu_sync *rsp)
{
	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_IDLE);
	WARN_ON_ONCE(READ_ONCE(rsp->gp_count) == 0);

	spin_lock_irq(&rsp->rss_lock);
	if (!--rsp->gp_count) {
		if (rsp->gp_state == GP_PASSED) {
			WRITE_ONCE(rsp->gp_state, GP_EXIT);
			rcu_sync_call(rsp);
		} else if (rsp->gp_state == GP_EXIT) {
			WRITE_ONCE(rsp->gp_state, GP_REPLAY);
		}
	}
	spin_unlock_irq(&rsp->rss_lock);
}