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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/ * cpu_preemption_locks ; 
 int /*<<< orphan*/  lock_impl_unlock (int /*<<< orphan*/ *) ; 
 int preempt_disable_count ; 
 size_t thread_cpu_id ; 

void preempt_enable(void)
{
	BUG_ON(preempt_disable_count < 1);

	if (--preempt_disable_count)
		return;

	lock_impl_unlock(&cpu_preemption_locks[thread_cpu_id]);
}