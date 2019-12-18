#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * first_child; } ;
typedef  TYPE_1__ pairingheap_node ;
struct TYPE_10__ {TYPE_5__* ph_root; } ;
typedef  TYPE_2__ pairingheap ;
struct TYPE_11__ {int /*<<< orphan*/ * next_sibling; int /*<<< orphan*/ * prev_or_parent; } ;

/* Variables and functions */
 TYPE_5__* merge (TYPE_2__*,TYPE_5__*,TYPE_1__*) ; 

void
pairingheap_add(pairingheap *heap, pairingheap_node *node)
{
	node->first_child = NULL;

	/* Link the new node as a new tree */
	heap->ph_root = merge(heap, heap->ph_root, node);
	heap->ph_root->prev_or_parent = NULL;
	heap->ph_root->next_sibling = NULL;
}