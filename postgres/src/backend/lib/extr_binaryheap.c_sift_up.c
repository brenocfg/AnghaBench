#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* bh_compare ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  bh_arg; int /*<<< orphan*/ * bh_nodes; } ;
typedef  TYPE_1__ binaryheap ;

/* Variables and functions */
 int parent_offset (int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_nodes (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
sift_up(binaryheap *heap, int node_off)
{
	while (node_off != 0)
	{
		int			cmp;
		int			parent_off;

		/*
		 * If this node is smaller than its parent, the heap condition is
		 * satisfied, and we're done.
		 */
		parent_off = parent_offset(node_off);
		cmp = heap->bh_compare(heap->bh_nodes[node_off],
							   heap->bh_nodes[parent_off],
							   heap->bh_arg);
		if (cmp <= 0)
			break;

		/*
		 * Otherwise, swap the node and its parent and go on to check the
		 * node's new parent.
		 */
		swap_nodes(heap, node_off, parent_off);
		node_off = parent_off;
	}
}