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
 int /*<<< orphan*/  RCU_SCHEDULER_INIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ nr_context_switches () ; 
 int num_online_cpus () ; 
 int /*<<< orphan*/  rcu_scheduler_active ; 
 int /*<<< orphan*/  rcu_test_sync_prims () ; 

void rcu_scheduler_starting(void)
{
	WARN_ON(num_online_cpus() != 1);
	WARN_ON(nr_context_switches() > 0);
	rcu_test_sync_prims();
	rcu_scheduler_active = RCU_SCHEDULER_INIT;
	rcu_test_sync_prims();
}