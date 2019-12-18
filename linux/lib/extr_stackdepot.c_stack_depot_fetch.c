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
struct stack_record {unsigned long* entries; unsigned int size; } ;
typedef  int /*<<< orphan*/  depot_stack_handle_t ;

/* Variables and functions */
 size_t STACK_ALLOC_ALIGN ; 
 void** stack_slabs ; 

unsigned int stack_depot_fetch(depot_stack_handle_t handle,
			       unsigned long **entries)
{
	union handle_parts parts = { .handle = handle };
	void *slab = stack_slabs[parts.slabindex];
	size_t offset = parts.offset << STACK_ALLOC_ALIGN;
	struct stack_record *stack = slab + offset;

	*entries = stack->entries;
	return stack->size;
}