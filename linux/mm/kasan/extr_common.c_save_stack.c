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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  depot_stack_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned long*) ; 
 int KASAN_STACK_DEPTH ; 
 unsigned int filter_irq_stacks (unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  stack_depot_save (unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int stack_trace_save (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline depot_stack_handle_t save_stack(gfp_t flags)
{
	unsigned long entries[KASAN_STACK_DEPTH];
	unsigned int nr_entries;

	nr_entries = stack_trace_save(entries, ARRAY_SIZE(entries), 0);
	nr_entries = filter_irq_stacks(entries, nr_entries);
	return stack_depot_save(entries, nr_entries, flags);
}