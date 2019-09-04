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
struct trace_seq {int dummy; } ;
struct fgraph_data {int /*<<< orphan*/  cpu_data; } ;
typedef  int pid_t ;
struct TYPE_2__ {int last_pid; } ;

/* Variables and functions */
 TYPE_1__* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_graph_cpu (struct trace_seq*,int) ; 
 int /*<<< orphan*/  print_graph_proc (struct trace_seq*,int) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static void
verif_pid(struct trace_seq *s, pid_t pid, int cpu, struct fgraph_data *data)
{
	pid_t prev_pid;
	pid_t *last_pid;

	if (!data)
		return;

	last_pid = &(per_cpu_ptr(data->cpu_data, cpu)->last_pid);

	if (*last_pid == pid)
		return;

	prev_pid = *last_pid;
	*last_pid = pid;

	if (prev_pid == -1)
		return;
/*
 * Context-switch trace line:

 ------------------------------------------
 | 1)  migration/0--1  =>  sshd-1755
 ------------------------------------------

 */
	trace_seq_puts(s, " ------------------------------------------\n");
	print_graph_cpu(s, cpu);
	print_graph_proc(s, prev_pid);
	trace_seq_puts(s, " => ");
	print_graph_proc(s, pid);
	trace_seq_puts(s, "\n ------------------------------------------\n\n");
}