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
struct assoc_array_shortcut {int parent_slot; int /*<<< orphan*/  back_pointer; int /*<<< orphan*/  next_node; } ;
struct assoc_array_ptr {int dummy; } ;
struct assoc_array_node {int parent_slot; int /*<<< orphan*/  back_pointer; int /*<<< orphan*/ * slots; } ;

/* Variables and functions */
 int ASSOC_ARRAY_FAN_OUT ; 
 unsigned long ASSOC_ARRAY_PTR_META_TYPE ; 
 struct assoc_array_ptr* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ assoc_array_ptr_is_leaf (struct assoc_array_ptr const*) ; 
 scalar_t__ assoc_array_ptr_is_meta (struct assoc_array_ptr const*) ; 
 scalar_t__ assoc_array_ptr_is_shortcut (struct assoc_array_ptr const*) ; 
 void const* assoc_array_ptr_to_leaf (struct assoc_array_ptr const*) ; 
 struct assoc_array_node* assoc_array_ptr_to_node (struct assoc_array_ptr const*) ; 
 struct assoc_array_shortcut* assoc_array_ptr_to_shortcut (struct assoc_array_ptr const*) ; 

__attribute__((used)) static int assoc_array_subtree_iterate(const struct assoc_array_ptr *root,
				       const struct assoc_array_ptr *stop,
				       int (*iterator)(const void *leaf,
						       void *iterator_data),
				       void *iterator_data)
{
	const struct assoc_array_shortcut *shortcut;
	const struct assoc_array_node *node;
	const struct assoc_array_ptr *cursor, *ptr, *parent;
	unsigned long has_meta;
	int slot, ret;

	cursor = root;

begin_node:
	if (assoc_array_ptr_is_shortcut(cursor)) {
		/* Descend through a shortcut */
		shortcut = assoc_array_ptr_to_shortcut(cursor);
		cursor = READ_ONCE(shortcut->next_node); /* Address dependency. */
	}

	node = assoc_array_ptr_to_node(cursor);
	slot = 0;

	/* We perform two passes of each node.
	 *
	 * The first pass does all the leaves in this node.  This means we
	 * don't miss any leaves if the node is split up by insertion whilst
	 * we're iterating over the branches rooted here (we may, however, see
	 * some leaves twice).
	 */
	has_meta = 0;
	for (; slot < ASSOC_ARRAY_FAN_OUT; slot++) {
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		has_meta |= (unsigned long)ptr;
		if (ptr && assoc_array_ptr_is_leaf(ptr)) {
			/* We need a barrier between the read of the pointer,
			 * which is supplied by the above READ_ONCE().
			 */
			/* Invoke the callback */
			ret = iterator(assoc_array_ptr_to_leaf(ptr),
				       iterator_data);
			if (ret)
				return ret;
		}
	}

	/* The second pass attends to all the metadata pointers.  If we follow
	 * one of these we may find that we don't come back here, but rather go
	 * back to a replacement node with the leaves in a different layout.
	 *
	 * We are guaranteed to make progress, however, as the slot number for
	 * a particular portion of the key space cannot change - and we
	 * continue at the back pointer + 1.
	 */
	if (!(has_meta & ASSOC_ARRAY_PTR_META_TYPE))
		goto finished_node;
	slot = 0;

continue_node:
	node = assoc_array_ptr_to_node(cursor);
	for (; slot < ASSOC_ARRAY_FAN_OUT; slot++) {
		ptr = READ_ONCE(node->slots[slot]); /* Address dependency. */
		if (assoc_array_ptr_is_meta(ptr)) {
			cursor = ptr;
			goto begin_node;
		}
	}

finished_node:
	/* Move up to the parent (may need to skip back over a shortcut) */
	parent = READ_ONCE(node->back_pointer); /* Address dependency. */
	slot = node->parent_slot;
	if (parent == stop)
		return 0;

	if (assoc_array_ptr_is_shortcut(parent)) {
		shortcut = assoc_array_ptr_to_shortcut(parent);
		cursor = parent;
		parent = READ_ONCE(shortcut->back_pointer); /* Address dependency. */
		slot = shortcut->parent_slot;
		if (parent == stop)
			return 0;
	}

	/* Ascend to next slot in parent node */
	cursor = parent;
	slot++;
	goto continue_node;
}