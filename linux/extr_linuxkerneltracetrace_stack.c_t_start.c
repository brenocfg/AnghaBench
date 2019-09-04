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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 void* __next (struct seq_file*,scalar_t__*) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_stack_tracer ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  stack_trace_max_lock ; 

__attribute__((used)) static void *t_start(struct seq_file *m, loff_t *pos)
{
	local_irq_disable();

	__this_cpu_inc(disable_stack_tracer);

	arch_spin_lock(&stack_trace_max_lock);

	if (*pos == 0)
		return SEQ_START_TOKEN;

	return __next(m, pos);
}