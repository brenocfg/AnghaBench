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
struct trace_array {TYPE_1__ trace_buffer; } ;
struct ftrace_graph_ret {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_NOTRACE_BIT ; 
 int /*<<< orphan*/  __trace_graph_return (struct trace_array*,struct ftrace_graph_ret*,unsigned long,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftrace_graph_addr_finish (struct ftrace_graph_ret*) ; 
 struct trace_array* graph_array ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct trace_array_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_recursion_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_recursion_test (int /*<<< orphan*/ ) ; 

void trace_graph_return(struct ftrace_graph_ret *trace)
{
	struct trace_array *tr = graph_array;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int cpu;
	int pc;

	ftrace_graph_addr_finish(trace);

	if (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT)) {
		trace_recursion_clear(TRACE_GRAPH_NOTRACE_BIT);
		return;
	}

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->trace_buffer.data, cpu);
	disabled = atomic_inc_return(&data->disabled);
	if (likely(disabled == 1)) {
		pc = preempt_count();
		__trace_graph_return(tr, trace, flags, pc);
	}
	atomic_dec(&data->disabled);
	local_irq_restore(flags);
}