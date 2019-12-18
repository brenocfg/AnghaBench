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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rcu_preempt_deferred_qs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_qs () ; 

void rcu_softirq_qs(void)
{
	rcu_qs();
	rcu_preempt_deferred_qs(current);
}