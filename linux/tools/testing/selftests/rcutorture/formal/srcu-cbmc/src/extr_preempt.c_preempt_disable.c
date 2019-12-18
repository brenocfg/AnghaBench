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
 scalar_t__ INT_MAX ; 
 size_t NR_CPUS ; 
 int /*<<< orphan*/  assume (int) ; 
 int /*<<< orphan*/ * cpu_preemption_locks ; 
 int /*<<< orphan*/  lock_impl_lock (int /*<<< orphan*/ *) ; 
 size_t nondet_int () ; 
 scalar_t__ preempt_disable_count ; 
 size_t thread_cpu_id ; 

void preempt_disable(void)
{
	BUG_ON(preempt_disable_count < 0 || preempt_disable_count == INT_MAX);

	if (preempt_disable_count++)
		return;

	thread_cpu_id = nondet_int();
	assume(thread_cpu_id >= 0);
	assume(thread_cpu_id < NR_CPUS);
	lock_impl_lock(&cpu_preemption_locks[thread_cpu_id]);
}