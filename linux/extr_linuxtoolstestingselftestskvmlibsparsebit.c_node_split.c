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
struct node {int idx; int num_after; int mask; } ;
typedef  int sparsebit_num_t ;
typedef  int sparsebit_idx_t ;
typedef  int mask_t ;

/* Variables and functions */
 int MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct node* node_add (struct sparsebit*,int) ; 
 struct node* node_find (struct sparsebit*,int) ; 

__attribute__((used)) static struct node *node_split(struct sparsebit *s, sparsebit_idx_t idx)
{
	struct node *nodep1, *nodep2;
	sparsebit_idx_t offset;
	sparsebit_num_t orig_num_after;

	assert(!(idx % MASK_BITS));

	/*
	 * Is there a node that describes the setting of idx?
	 * If not, add it.
	 */
	nodep1 = node_find(s, idx);
	if (!nodep1)
		return node_add(s, idx);

	/*
	 * All done if the starting index of the node is where the
	 * split should occur.
	 */
	if (nodep1->idx == idx)
		return nodep1;

	/*
	 * Split point not at start of mask, so it must be part of
	 * bits described by num_after.
	 */

	/*
	 * Calculate offset within num_after for where the split is
	 * to occur.
	 */
	offset = idx - (nodep1->idx + MASK_BITS);
	orig_num_after = nodep1->num_after;

	/*
	 * Add a new node to describe the bits starting at
	 * the split point.
	 */
	nodep1->num_after = offset;
	nodep2 = node_add(s, idx);

	/* Move bits after the split point into the new node */
	nodep2->num_after = orig_num_after - offset;
	if (nodep2->num_after >= MASK_BITS) {
		nodep2->mask = ~(mask_t) 0;
		nodep2->num_after -= MASK_BITS;
	} else {
		nodep2->mask = (1 << nodep2->num_after) - 1;
		nodep2->num_after = 0;
	}

	return nodep2;
}