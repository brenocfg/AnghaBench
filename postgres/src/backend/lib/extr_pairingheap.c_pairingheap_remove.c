#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* prev_or_parent; struct TYPE_9__* next_sibling; struct TYPE_9__* first_child; } ;
typedef  TYPE_1__ pairingheap_node ;
struct TYPE_10__ {TYPE_1__* ph_root; } ;
typedef  TYPE_2__ pairingheap ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_1__* merge_children (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pairingheap_remove_first (TYPE_2__*) ; 

void
pairingheap_remove(pairingheap *heap, pairingheap_node *node)
{
	pairingheap_node *children;
	pairingheap_node *replacement;
	pairingheap_node *next_sibling;
	pairingheap_node **prev_ptr;

	/*
	 * If the removed node happens to be the root node, do it with
	 * pairingheap_remove_first().
	 */
	if (node == heap->ph_root)
	{
		(void) pairingheap_remove_first(heap);
		return;
	}

	/*
	 * Before we modify anything, remember the removed node's first_child and
	 * next_sibling pointers.
	 */
	children = node->first_child;
	next_sibling = node->next_sibling;

	/*
	 * Also find the pointer to the removed node in its previous sibling, or
	 * if this is the first child of its parent, in its parent.
	 */
	if (node->prev_or_parent->first_child == node)
		prev_ptr = &node->prev_or_parent->first_child;
	else
		prev_ptr = &node->prev_or_parent->next_sibling;
	Assert(*prev_ptr == node);

	/*
	 * If this node has children, make a new subheap of the children and link
	 * the subheap in place of the removed node. Otherwise just unlink this
	 * node.
	 */
	if (children)
	{
		replacement = merge_children(heap, children);

		replacement->prev_or_parent = node->prev_or_parent;
		replacement->next_sibling = node->next_sibling;
		*prev_ptr = replacement;
		if (next_sibling)
			next_sibling->prev_or_parent = replacement;
	}
	else
	{
		*prev_ptr = next_sibling;
		if (next_sibling)
			next_sibling->prev_or_parent = node->prev_or_parent;
	}
}