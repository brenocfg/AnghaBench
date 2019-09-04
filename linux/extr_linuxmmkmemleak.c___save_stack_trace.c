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
struct stack_trace {int nr_entries; unsigned long* entries; int skip; int /*<<< orphan*/  max_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  save_stack_trace (struct stack_trace*) ; 

__attribute__((used)) static int __save_stack_trace(unsigned long *trace)
{
	struct stack_trace stack_trace;

	stack_trace.max_entries = MAX_TRACE;
	stack_trace.nr_entries = 0;
	stack_trace.entries = trace;
	stack_trace.skip = 2;
	save_stack_trace(&stack_trace);

	return stack_trace.nr_entries;
}