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
 scalar_t__ RCU_SCHEDULER_INIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_expedited ; 
 int /*<<< orphan*/  rcu_expedited_nesting ; 
 scalar_t__ rcu_scheduler_active ; 

bool rcu_gp_is_expedited(void)
{
	return rcu_expedited || atomic_read(&rcu_expedited_nesting) ||
	       rcu_scheduler_active == RCU_SCHEDULER_INIT;
}