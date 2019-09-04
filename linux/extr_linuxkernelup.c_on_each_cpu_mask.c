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

/* Variables and functions */
 scalar_t__ cpumask_test_cpu (int /*<<< orphan*/ ,struct cpumask const*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

void on_each_cpu_mask(const struct cpumask *mask,
		      smp_call_func_t func, void *info, bool wait)
{
	unsigned long flags;

	if (cpumask_test_cpu(0, mask)) {
		local_irq_save(flags);
		func(info);
		local_irq_restore(flags);
	}
}