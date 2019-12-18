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
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  (* smp_call_func_t ) (void*) ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void on_each_cpu_cond_mask(bool (*cond_func)(int cpu, void *info),
			   smp_call_func_t func, void *info, bool wait,
			   gfp_t gfp_flags, const struct cpumask *mask)
{
	unsigned long flags;

	preempt_disable();
	if (cond_func(0, info)) {
		local_irq_save(flags);
		func(info);
		local_irq_restore(flags);
	}
	preempt_enable();
}