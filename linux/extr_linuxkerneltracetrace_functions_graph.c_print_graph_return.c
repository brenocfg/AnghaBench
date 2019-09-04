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
typedef  int u32 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {int cpu; struct trace_array* tr; struct fgraph_data* private; } ;
struct trace_entry {int /*<<< orphan*/  pid; } ;
struct trace_array {int dummy; } ;
struct ftrace_graph_ret {unsigned long long rettime; unsigned long long calltime; int depth; scalar_t__ func; void* overrun; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;
struct fgraph_cpu_data {int depth; scalar_t__* enter_funcs; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int FTRACE_RETFUNC_DEPTH ; 
 int TRACE_GRAPH_INDENT ; 
 int TRACE_GRAPH_PRINT_OVERRUN ; 
 int TRACE_GRAPH_PRINT_TAIL ; 
 int /*<<< orphan*/  TRACE_GRAPH_RET ; 
 int TRACE_TYPE_HANDLED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ check_irq_return (struct trace_iterator*,int,int) ; 
 struct fgraph_cpu_data* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_graph_duration (struct trace_array*,unsigned long long,struct trace_seq*,int) ; 
 int /*<<< orphan*/  print_graph_irq (struct trace_iterator*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_graph_prologue (struct trace_iterator*,struct trace_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,void*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static enum print_line_t
print_graph_return(struct ftrace_graph_ret *trace, struct trace_seq *s,
		   struct trace_entry *ent, struct trace_iterator *iter,
		   u32 flags)
{
	unsigned long long duration = trace->rettime - trace->calltime;
	struct fgraph_data *data = iter->private;
	struct trace_array *tr = iter->tr;
	pid_t pid = ent->pid;
	int cpu = iter->cpu;
	int func_match = 1;
	int i;

	if (check_irq_return(iter, flags, trace->depth))
		return TRACE_TYPE_HANDLED;

	if (data) {
		struct fgraph_cpu_data *cpu_data;
		int cpu = iter->cpu;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);

		/*
		 * Comments display at + 1 to depth. This is the
		 * return from a function, we now want the comments
		 * to display at the same level of the bracket.
		 */
		cpu_data->depth = trace->depth - 1;

		if (trace->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(trace->depth < 0)) {
			if (cpu_data->enter_funcs[trace->depth] != trace->func)
				func_match = 0;
			cpu_data->enter_funcs[trace->depth] = 0;
		}
	}

	print_graph_prologue(iter, s, 0, 0, flags);

	/* Overhead and duration */
	print_graph_duration(tr, duration, s, flags);

	/* Closing brace */
	for (i = 0; i < trace->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_putc(s, ' ');

	/*
	 * If the return function does not have a matching entry,
	 * then the entry was lost. Instead of just printing
	 * the '}' and letting the user guess what function this
	 * belongs to, write out the function name. Always do
	 * that if the funcgraph-tail option is enabled.
	 */
	if (func_match && !(flags & TRACE_GRAPH_PRINT_TAIL))
		trace_seq_puts(s, "}\n");
	else
		trace_seq_printf(s, "} /* %ps */\n", (void *)trace->func);

	/* Overrun */
	if (flags & TRACE_GRAPH_PRINT_OVERRUN)
		trace_seq_printf(s, " (Overruns: %lu)\n",
				 trace->overrun);

	print_graph_irq(iter, trace->func, TRACE_GRAPH_RET,
			cpu, pid, flags);

	return trace_handle_return(s);
}