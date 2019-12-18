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

/* Variables and functions */
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int,char*) ; 
 scalar_t__ lock_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_bh_lock_map ; 
 int /*<<< orphan*/  rcu_lock_map ; 
 int /*<<< orphan*/  rcu_sched_lock_map ; 

void synchronize_rcu(void)
{
	RCU_LOCKDEP_WARN(lock_is_held(&rcu_bh_lock_map) ||
			 lock_is_held(&rcu_lock_map) ||
			 lock_is_held(&rcu_sched_lock_map),
			 "Illegal synchronize_rcu() in RCU read-side critical section");
}