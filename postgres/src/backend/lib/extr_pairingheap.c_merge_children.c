#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next_sibling; } ;
typedef  TYPE_1__ pairingheap_node ;
typedef  int /*<<< orphan*/  pairingheap ;

/* Variables and functions */
 TYPE_1__* merge (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static pairingheap_node *
merge_children(pairingheap *heap, pairingheap_node *children)
{
	pairingheap_node *curr,
			   *next;
	pairingheap_node *pairs;
	pairingheap_node *newroot;

	if (children == NULL || children->next_sibling == NULL)
		return children;

	/* Walk the subheaps from left to right, merging in pairs */
	next = children;
	pairs = NULL;
	for (;;)
	{
		curr = next;

		if (curr == NULL)
			break;

		if (curr->next_sibling == NULL)
		{
			/* last odd node at the end of list */
			curr->next_sibling = pairs;
			pairs = curr;
			break;
		}

		next = curr->next_sibling->next_sibling;

		/* merge this and the next subheap, and add to 'pairs' list. */

		curr = merge(heap, curr, curr->next_sibling);
		curr->next_sibling = pairs;
		pairs = curr;
	}

	/*
	 * Merge all the pairs together to form a single heap.
	 */
	newroot = pairs;
	next = pairs->next_sibling;
	while (next)
	{
		curr = next;
		next = curr->next_sibling;

		newroot = merge(heap, newroot, curr);
	}

	return newroot;
}