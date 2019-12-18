#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rcu_need_heavy_qs; int /*<<< orphan*/  rcu_urgent_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS (char*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  raw_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_data ; 
 int /*<<< orphan*/  rcu_momentary_dyntick_idle () ; 
 int /*<<< orphan*/  rcu_qs () ; 
 int /*<<< orphan*/  rcu_tasks_qs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rcu_utilization (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void rcu_note_context_switch(bool preempt)
{
	trace_rcu_utilization(TPS("Start context switch"));
	rcu_qs();
	/* Load rcu_urgent_qs before other flags. */
	if (!smp_load_acquire(this_cpu_ptr(&rcu_data.rcu_urgent_qs)))
		goto out;
	this_cpu_write(rcu_data.rcu_urgent_qs, false);
	if (unlikely(raw_cpu_read(rcu_data.rcu_need_heavy_qs)))
		rcu_momentary_dyntick_idle();
	if (!preempt)
		rcu_tasks_qs(current);
out:
	trace_rcu_utilization(TPS("End context switch"));
}