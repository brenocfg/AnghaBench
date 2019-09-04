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
union handle_parts {size_t slabindex; size_t offset; int /*<<< orphan*/  handle; } ;
struct stack_trace {scalar_t__ skip; int /*<<< orphan*/  entries; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  nr_entries; } ;
struct stack_record {int /*<<< orphan*/  entries; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  depot_stack_handle_t ;

/* Variables and functions */
 size_t STACK_ALLOC_ALIGN ; 
 void** stack_slabs ; 

void depot_fetch_stack(depot_stack_handle_t handle, struct stack_trace *trace)
{
	union handle_parts parts = { .handle = handle };
	void *slab = stack_slabs[parts.slabindex];
	size_t offset = parts.offset << STACK_ALLOC_ALIGN;
	struct stack_record *stack = slab + offset;

	trace->nr_entries = trace->max_entries = stack->size;
	trace->entries = stack->entries;
	trace->skip = 0;
}