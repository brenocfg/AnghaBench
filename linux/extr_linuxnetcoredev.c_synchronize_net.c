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
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ rtnl_is_locked () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  synchronize_rcu_expedited () ; 

void synchronize_net(void)
{
	might_sleep();
	if (rtnl_is_locked())
		synchronize_rcu_expedited();
	else
		synchronize_rcu();
}