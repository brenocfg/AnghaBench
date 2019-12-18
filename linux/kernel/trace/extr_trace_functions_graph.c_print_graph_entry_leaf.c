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
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;
struct trace_iterator {int cpu; TYPE_1__* ent; struct trace_array* tr; struct fgraph_data* private; } ;
struct trace_array {int dummy; } ;
struct ftrace_graph_ret {unsigned long long rettime; unsigned long long calltime; int /*<<< orphan*/  func; } ;
struct ftrace_graph_ret_entry {struct ftrace_graph_ret ret; } ;
struct ftrace_graph_ent {int depth; scalar_t__ func; } ;
struct ftrace_graph_ent_entry {struct ftrace_graph_ent graph_ent; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;
struct fgraph_cpu_data {int depth; scalar_t__* enter_funcs; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int FTRACE_RETFUNC_DEPTH ; 
 int TRACE_GRAPH_INDENT ; 
 int /*<<< orphan*/  TRACE_GRAPH_RET ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct fgraph_cpu_data* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_graph_duration (struct trace_array*,unsigned long long,struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_graph_irq (struct trace_iterator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int trace_handle_return (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,void*) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,char) ; 

__attribute__((used)) static enum print_line_t
print_graph_entry_leaf(struct trace_iterator *iter,
		struct ftrace_graph_ent_entry *entry,
		struct ftrace_graph_ret_entry *ret_entry,
		struct trace_seq *s, u32 flags)
{
	struct fgraph_data *data = iter->private;
	struct trace_array *tr = iter->tr;
	struct ftrace_graph_ret *graph_ret;
	struct ftrace_graph_ent *call;
	unsigned long long duration;
	int cpu = iter->cpu;
	int i;

	graph_ret = &ret_entry->ret;
	call = &entry->graph_ent;
	duration = graph_ret->rettime - graph_ret->calltime;

	if (data) {
		struct fgraph_cpu_data *cpu_data;

		cpu_data = per_cpu_ptr(data->cpu_data, cpu);

		/*
		 * Comments display at + 1 to depth. Since
		 * this is a leaf function, keep the comments
		 * equal to this depth.
		 */
		cpu_data->depth = call->depth - 1;

		/* No need to keep this function around for this depth */
		if (call->depth < FTRACE_RETFUNC_DEPTH &&
		    !WARN_ON_ONCE(call->depth < 0))
			cpu_data->enter_funcs[call->depth] = 0;
	}

	/* Overhead and duration */
	print_graph_duration(tr, duration, s, flags);

	/* Function */
	for (i = 0; i < call->depth * TRACE_GRAPH_INDENT; i++)
		trace_seq_putc(s, ' ');

	trace_seq_printf(s, "%ps();\n", (void *)call->func);

	print_graph_irq(iter, graph_ret->func, TRACE_GRAPH_RET,
			cpu, iter->ent->pid, flags);

	return trace_handle_return(s);
}