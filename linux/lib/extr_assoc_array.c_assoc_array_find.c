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
struct TYPE_2__ {struct assoc_array_node* node; } ;
struct assoc_array_walk_result {TYPE_1__ terminal_node; } ;
struct assoc_array_ptr {int dummy; } ;
struct assoc_array_ops {scalar_t__ (* compare_object ) (void const*,void const*) ;} ;
struct assoc_array_node {int /*<<< orphan*/ * slots; } ;
struct assoc_array {int dummy; } ;

/* Variables and functions */
 int ASSOC_ARRAY_FAN_OUT ; 
 struct assoc_array_ptr* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ assoc_array_ptr_is_leaf (struct assoc_array_ptr const*) ; 
 void* assoc_array_ptr_to_leaf (struct assoc_array_ptr const*) ; 
 scalar_t__ assoc_array_walk (struct assoc_array const*,struct assoc_array_ops const*,void const*,struct assoc_array_walk_result*) ; 
 scalar_t__ assoc_array_walk_found_terminal_node ; 
 scalar_t__ stub1 (void const*,void const*) ; 

void *assoc_array_find(const struct assoc_array *array,
		       const struct assoc_array_ops *ops,
		       const void *index_key)
{
	struct assoc_array_walk_result result;
	const struct assoc_array_node *node;
	const struct assoc_array_ptr *ptr;
	const void *leaf;
	int slot;

	if (assoc_array_walk(array, ops, index_key, &result) !=
	    assoc_array_walk_found_terminal_node)
		return NULL;

	node = result.terminal_node.node;

	/* If the target key is available to us, it's has to be pointed to by
	 * the terminal node.
	 */
	for (slot = 0; slot < ASSOC_ARRAY_FAN_OUT; slot++) {
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		if (ptr && assoc_array_ptr_is_leaf(ptr)) {
			/* We need a barrier between the read of the pointer
			 * and dereferencing the pointer - but only if we are
			 * actually going to dereference it.
			 */
			leaf = assoc_array_ptr_to_leaf(ptr);
			if (ops->compare_object(leaf, index_key))
				return (void *)leaf;
		}
	}

	return NULL;
}