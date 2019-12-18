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
struct trace_array_cpu {int /*<<< orphan*/  disabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct trace_array {TYPE_1__ trace_buffer; int /*<<< orphan*/  function_enabled; } ;
struct pt_regs {int dummy; } ;
struct ftrace_ops {struct trace_array* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_SKIP ; 
 int /*<<< orphan*/  __trace_stack (struct trace_array*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct trace_array_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_function (struct trace_array*,unsigned long,unsigned long,unsigned long,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
function_stack_trace_call(unsigned long ip, unsigned long parent_ip,
			  struct ftrace_ops *op, struct pt_regs *pt_regs)
{
	struct trace_array *tr = op->private;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int cpu;
	int pc;

	if (unlikely(!tr->function_enabled))
		return;

	/*
	 * Need to use raw, since this must be called before the
	 * recursive protection is performed.
	 */
	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->trace_buffer.data, cpu);
	disabled = atomic_inc_return(&data->disabled);

	if (likely(disabled == 1)) {
		pc = preempt_count();
		trace_function(tr, ip, parent_ip, flags, pc);
		__trace_stack(tr, flags, STACK_SKIP, pc);
	}

	atomic_dec(&data->disabled);
	local_irq_restore(flags);
}