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

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,void*) ; 
 unsigned long* stack_dump_trace ; 

__attribute__((used)) static void trace_lookup_stack(struct seq_file *m, long i)
{
	unsigned long addr = stack_dump_trace[i];

	seq_printf(m, "%pS\n", (void *)addr);
}