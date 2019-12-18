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
struct ftrace_graph_ent {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_GRAPH_NOTRACE_BIT ; 
 int __trace_graph_entry (struct trace_array*,struct ftrace_graph_ent*,unsigned long,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 long atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ ftrace_graph_ignore_func (struct ftrace_graph_ent*) ; 
 scalar_t__ ftrace_graph_ignore_irqs () ; 
 scalar_t__ ftrace_graph_notrace_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_trace_task (struct trace_array*) ; 
 struct trace_array* graph_array ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct trace_array_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_recursion_set (int /*<<< orphan*/ ) ; 
 scalar_t__ trace_recursion_test (int /*<<< orphan*/ ) ; 
 scalar_t__ tracing_thresh ; 

int trace_graph_entry(struct ftrace_graph_ent *trace)
{
	struct trace_array *tr = graph_array;
	struct trace_array_cpu *data;
	unsigned long flags;
	long disabled;
	int ret;
	int cpu;
	int pc;

	if (trace_recursion_test(TRACE_GRAPH_NOTRACE_BIT))
		return 0;

	/*
	 * Do not trace a function if it's filtered by set_graph_notrace.
	 * Make the index of ret stack negative to indicate that it should
	 * ignore further functions.  But it needs its own ret stack entry
	 * to recover the original index in order to continue tracing after
	 * returning from the function.
	 */
	if (ftrace_graph_notrace_addr(trace->func)) {
		trace_recursion_set(TRACE_GRAPH_NOTRACE_BIT);
		/*
		 * Need to return 1 to have the return called
		 * that will clear the NOTRACE bit.
		 */
		return 1;
	}

	if (!ftrace_trace_task(tr))
		return 0;

	if (ftrace_graph_ignore_func(trace))
		return 0;

	if (ftrace_graph_ignore_irqs())
		return 0;

	/*
	 * Stop here if tracing_threshold is set. We only write function return
	 * events to the ring buffer.
	 */
	if (tracing_thresh)
		return 1;

	local_irq_save(flags);
	cpu = raw_smp_processor_id();
	data = per_cpu_ptr(tr->trace_buffer.data, cpu);
	disabled = atomic_inc_return(&data->disabled);
	if (likely(disabled == 1)) {
		pc = preempt_count();
		ret = __trace_graph_entry(tr, trace, flags, pc);
	} else {
		ret = 0;
	}

	atomic_dec(&data->disabled);
	local_irq_restore(flags);

	return ret;
}