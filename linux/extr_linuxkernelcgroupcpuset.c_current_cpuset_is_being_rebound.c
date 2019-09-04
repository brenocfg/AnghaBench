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
 scalar_t__ cpuset_being_rebound ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ task_cs (int /*<<< orphan*/ ) ; 

bool current_cpuset_is_being_rebound(void)
{
	bool ret;

	rcu_read_lock();
	ret = task_cs(current) == cpuset_being_rebound;
	rcu_read_unlock();

	return ret;
}