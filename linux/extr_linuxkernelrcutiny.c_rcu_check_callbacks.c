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
 int /*<<< orphan*/  in_softirq () ; 
 int /*<<< orphan*/  rcu_bh_qs () ; 
 int /*<<< orphan*/  rcu_sched_qs () ; 

void rcu_check_callbacks(int user)
{
	if (user)
		rcu_sched_qs();
	if (user || !in_softirq())
		rcu_bh_qs();
}