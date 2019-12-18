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
struct rcu_sync {int gp_count; int gp_state; int /*<<< orphan*/  rss_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP_EXIT ; 
 int GP_IDLE ; 
 scalar_t__ GP_PASSED ; 
 int GP_REPLAY ; 
 scalar_t__ READ_ONCE (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rcu_sync_dtor(struct rcu_sync *rsp)
{
	int gp_state;

	WARN_ON_ONCE(READ_ONCE(rsp->gp_count));
	WARN_ON_ONCE(READ_ONCE(rsp->gp_state) == GP_PASSED);

	spin_lock_irq(&rsp->rss_lock);
	if (rsp->gp_state == GP_REPLAY)
		WRITE_ONCE(rsp->gp_state, GP_EXIT);
	gp_state = rsp->gp_state;
	spin_unlock_irq(&rsp->rss_lock);

	if (gp_state != GP_IDLE) {
		rcu_barrier();
		WARN_ON_ONCE(rsp->gp_state != GP_IDLE);
	}
}