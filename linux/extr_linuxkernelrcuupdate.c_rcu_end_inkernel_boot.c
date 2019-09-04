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
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_normal ; 
 scalar_t__ rcu_normal_after_boot ; 
 int /*<<< orphan*/  rcu_unexpedite_gp () ; 

void rcu_end_inkernel_boot(void)
{
	rcu_unexpedite_gp();
	if (rcu_normal_after_boot)
		WRITE_ONCE(rcu_normal, 1);
}