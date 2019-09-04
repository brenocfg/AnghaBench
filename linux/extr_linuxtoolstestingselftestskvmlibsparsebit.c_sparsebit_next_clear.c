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
struct sparsebit {int dummy; } ;
struct node {scalar_t__ idx; int mask; scalar_t__ num_after; } ;
typedef  scalar_t__ sparsebit_idx_t ;

/* Variables and functions */
 scalar_t__ MASK_BITS ; 
 struct node* node_find (struct sparsebit*,scalar_t__) ; 
 scalar_t__ node_first_clear (struct node*,int /*<<< orphan*/ ) ; 
 struct node* node_next (struct sparsebit*,struct node*) ; 

sparsebit_idx_t sparsebit_next_clear(struct sparsebit *s,
	sparsebit_idx_t prev)
{
	sparsebit_idx_t lowest_possible = prev + 1;
	sparsebit_idx_t idx;
	struct node *nodep1, *nodep2;

	/* A bit after the highest index can't be set. */
	if (lowest_possible == 0)
		return 0;

	/*
	 * Does a node describing the setting of lowest_possible exist?
	 * If not, the bit at lowest_possible is cleared.
	 */
	nodep1 = node_find(s, lowest_possible);
	if (!nodep1)
		return lowest_possible;

	/* Does a mask bit in node 1 describe the next cleared bit. */
	for (idx = lowest_possible - nodep1->idx; idx < MASK_BITS; idx++)
		if (!(nodep1->mask & (1 << idx)))
			return nodep1->idx + idx;

	/*
	 * Next cleared bit is not described by node 1.  If there
	 * isn't a next node, then next cleared bit is described
	 * by bit after the bits described by the first node.
	 */
	nodep2 = node_next(s, nodep1);
	if (!nodep2)
		return nodep1->idx + MASK_BITS + nodep1->num_after;

	/*
	 * There is a second node.
	 * If it is not adjacent to the first node, then there is a gap
	 * of cleared bits between the nodes, and the next cleared bit
	 * is the first bit within the gap.
	 */
	if (nodep1->idx + MASK_BITS + nodep1->num_after != nodep2->idx)
		return nodep1->idx + MASK_BITS + nodep1->num_after;

	/*
	 * Second node is adjacent to the first node.
	 * Because it is adjacent, its mask should be non-zero.  If all
	 * its mask bits are set, then with it being adjacent, it should
	 * have had the mask bits moved into the num_after setting of the
	 * previous node.
	 */
	return node_first_clear(nodep2, 0);
}