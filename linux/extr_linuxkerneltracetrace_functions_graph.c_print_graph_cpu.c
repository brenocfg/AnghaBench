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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max_bytes_for_cpu ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void print_graph_cpu(struct trace_seq *s, int cpu)
{
	/*
	 * Start with a space character - to make it stand out
	 * to the right a bit when trace output is pasted into
	 * email:
	 */
	trace_seq_printf(s, " %*d) ", max_bytes_for_cpu, cpu);
}