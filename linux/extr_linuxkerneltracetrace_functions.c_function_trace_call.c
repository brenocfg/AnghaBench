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
 int /*<<< orphan*/  TRACE_FTRACE_MAX ; 
 int /*<<< orphan*/  TRACE_FTRACE_START ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_save_flags (unsigned long) ; 
 struct trace_array_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  trace_clear_recursion (int) ; 
 int /*<<< orphan*/  trace_function (struct trace_array*,unsigned long,unsigned long,unsigned long,int) ; 
 int trace_test_and_set_recursion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
function_trace_call(unsigned long ip, unsigned long parent_ip,
		    struct ftrace_ops *op, struct pt_regs *pt_regs)
{
	struct trace_array *tr = op->private;
	struct trace_array_cpu *data;
	unsigned long flags;
	int bit;
	int cpu;
	int pc;

	if (unlikely(!tr->function_enabled))
		return;

	pc = preempt_count();
	preempt_disable_notrace();

	bit = trace_test_and_set_recursion(TRACE_FTRACE_START, TRACE_FTRACE_MAX);
	if (bit < 0)
		goto out;

	cpu = smp_processor_id();
	data = per_cpu_ptr(tr->trace_buffer.data, cpu);
	if (!atomic_read(&data->disabled)) {
		local_save_flags(flags);
		trace_function(tr, ip, parent_ip, flags, pc);
	}
	trace_clear_recursion(bit);

 out:
	preempt_enable_notrace();
}