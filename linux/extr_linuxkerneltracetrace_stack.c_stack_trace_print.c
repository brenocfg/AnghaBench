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
struct TYPE_2__ {long nr_entries; } ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  pr_emerg (char*,long,...) ; 
 scalar_t__* stack_dump_trace ; 
 int* stack_trace_index ; 
 TYPE_1__ stack_trace_max ; 

void stack_trace_print(void)
{
	long i;
	int size;

	pr_emerg("        Depth    Size   Location    (%d entries)\n"
			   "        -----    ----   --------\n",
			   stack_trace_max.nr_entries);

	for (i = 0; i < stack_trace_max.nr_entries; i++) {
		if (stack_dump_trace[i] == ULONG_MAX)
			break;
		if (i+1 == stack_trace_max.nr_entries ||
				stack_dump_trace[i+1] == ULONG_MAX)
			size = stack_trace_index[i];
		else
			size = stack_trace_index[i] - stack_trace_index[i+1];

		pr_emerg("%3ld) %8d   %5d   %pS\n", i, stack_trace_index[i],
				size, (void *)stack_dump_trace[i]);
	}
}