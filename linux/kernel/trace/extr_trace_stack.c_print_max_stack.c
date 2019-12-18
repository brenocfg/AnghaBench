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

/* Variables and functions */
 int /*<<< orphan*/  pr_emerg (char*,long,...) ; 
 scalar_t__* stack_dump_trace ; 
 int* stack_trace_index ; 
 long stack_trace_nr_entries ; 

__attribute__((used)) static void print_max_stack(void)
{
	long i;
	int size;

	pr_emerg("        Depth    Size   Location    (%d entries)\n"
			   "        -----    ----   --------\n",
			   stack_trace_nr_entries);

	for (i = 0; i < stack_trace_nr_entries; i++) {
		if (i + 1 == stack_trace_nr_entries)
			size = stack_trace_index[i];
		else
			size = stack_trace_index[i] - stack_trace_index[i+1];

		pr_emerg("%3ld) %8d   %5d   %pS\n", i, stack_trace_index[i],
				size, (void *)stack_dump_trace[i]);
	}
}