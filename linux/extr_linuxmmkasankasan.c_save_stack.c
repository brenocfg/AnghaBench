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
struct stack_trace {int nr_entries; unsigned long* entries; int max_entries; int /*<<< orphan*/  skip; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  depot_stack_handle_t ;

/* Variables and functions */
 int KASAN_STACK_DEPTH ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  depot_save_stack (struct stack_trace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_irq_stacks (struct stack_trace*) ; 
 int /*<<< orphan*/  save_stack_trace (struct stack_trace*) ; 

__attribute__((used)) static inline depot_stack_handle_t save_stack(gfp_t flags)
{
	unsigned long entries[KASAN_STACK_DEPTH];
	struct stack_trace trace = {
		.nr_entries = 0,
		.entries = entries,
		.max_entries = KASAN_STACK_DEPTH,
		.skip = 0
	};

	save_stack_trace(&trace);
	filter_irq_stacks(&trace);
	if (trace.nr_entries != 0 &&
	    trace.entries[trace.nr_entries-1] == ULONG_MAX)
		trace.nr_entries--;

	return depot_save_stack(&trace, flags);
}