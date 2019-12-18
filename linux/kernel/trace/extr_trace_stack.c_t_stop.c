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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_stack_tracer ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  stack_trace_max_lock ; 

__attribute__((used)) static void t_stop(struct seq_file *m, void *p)
{
	arch_spin_unlock(&stack_trace_max_lock);

	__this_cpu_dec(disable_stack_tracer);

	local_irq_enable();
}