#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rcu_qs_ctr; int /*<<< orphan*/  rcu_need_heavy_qs; int /*<<< orphan*/  rcu_urgent_qs; } ;
struct TYPE_5__ {int /*<<< orphan*/  exp; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct TYPE_7__ {TYPE_2__ cpu_no_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  raw_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_4__ rcu_dynticks ; 
 int /*<<< orphan*/  rcu_momentary_dyntick_idle () ; 
 TYPE_3__ rcu_sched_data ; 
 int /*<<< orphan*/  rcu_sched_qs () ; 
 int /*<<< orphan*/  smp_load_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void rcu_all_qs(void)
{
	unsigned long flags;

	if (!raw_cpu_read(rcu_dynticks.rcu_urgent_qs))
		return;
	preempt_disable();
	/* Load rcu_urgent_qs before other flags. */
	if (!smp_load_acquire(this_cpu_ptr(&rcu_dynticks.rcu_urgent_qs))) {
		preempt_enable();
		return;
	}
	this_cpu_write(rcu_dynticks.rcu_urgent_qs, false);
	barrier(); /* Avoid RCU read-side critical sections leaking down. */
	if (unlikely(raw_cpu_read(rcu_dynticks.rcu_need_heavy_qs))) {
		local_irq_save(flags);
		rcu_momentary_dyntick_idle();
		local_irq_restore(flags);
	}
	if (unlikely(raw_cpu_read(rcu_sched_data.cpu_no_qs.b.exp)))
		rcu_sched_qs();
	this_cpu_inc(rcu_dynticks.rcu_qs_ctr);
	barrier(); /* Avoid RCU read-side critical sections leaking up. */
	preempt_enable();
}