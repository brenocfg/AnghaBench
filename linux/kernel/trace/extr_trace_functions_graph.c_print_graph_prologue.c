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
struct trace_iterator {int cpu; int /*<<< orphan*/  ts; struct trace_array* tr; struct trace_entry* ent; struct fgraph_data* private; } ;
struct trace_entry {int /*<<< orphan*/  pid; } ;
struct trace_array {int trace_flags; } ;
struct fgraph_data {int dummy; } ;

/* Variables and functions */
 int TRACE_GRAPH_PRINT_ABS_TIME ; 
 int TRACE_GRAPH_PRINT_CPU ; 
 int TRACE_GRAPH_PRINT_PROC ; 
 int TRACE_GRAPH_PRINT_REL_TIME ; 
 int TRACE_ITER_CONTEXT_INFO ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int /*<<< orphan*/  print_graph_abs_time (int /*<<< orphan*/ ,struct trace_seq*) ; 
 int /*<<< orphan*/  print_graph_cpu (struct trace_seq*,int) ; 
 int /*<<< orphan*/  print_graph_irq (struct trace_iterator*,unsigned long,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_graph_lat_fmt (struct trace_seq*,struct trace_entry*) ; 
 int /*<<< orphan*/  print_graph_proc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_graph_rel_time (struct trace_iterator*,struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 
 int /*<<< orphan*/  verif_pid (struct trace_seq*,int /*<<< orphan*/ ,int,struct fgraph_data*) ; 

__attribute__((used)) static void
print_graph_prologue(struct trace_iterator *iter, struct trace_seq *s,
		     int type, unsigned long addr, u32 flags)
{
	struct fgraph_data *data = iter->private;
	struct trace_entry *ent = iter->ent;
	struct trace_array *tr = iter->tr;
	int cpu = iter->cpu;

	/* Pid */
	verif_pid(s, ent->pid, cpu, data);

	if (type)
		/* Interrupt */
		print_graph_irq(iter, addr, type, cpu, ent->pid, flags);

	if (!(tr->trace_flags & TRACE_ITER_CONTEXT_INFO))
		return;

	/* Absolute time */
	if (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		print_graph_abs_time(iter->ts, s);

	/* Relative time */
	if (flags & TRACE_GRAPH_PRINT_REL_TIME)
		print_graph_rel_time(iter, s);

	/* Cpu */
	if (flags & TRACE_GRAPH_PRINT_CPU)
		print_graph_cpu(s, cpu);

	/* Proc */
	if (flags & TRACE_GRAPH_PRINT_PROC) {
		print_graph_proc(s, ent->pid);
		trace_seq_puts(s, " | ");
	}

	/* Latency format */
	if (tr->trace_flags & TRACE_ITER_LATENCY_FMT)
		print_graph_lat_fmt(s, ent);

	return;
}