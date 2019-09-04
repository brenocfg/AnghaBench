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
struct sparsebit {scalar_t__ num_set; } ;
struct node {int idx; int mask; } ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 struct node* node_find (struct sparsebit*,int) ; 
 int /*<<< orphan*/  node_reduce (struct sparsebit*,struct node*) ; 
 struct node* node_split (struct sparsebit*,int) ; 
 scalar_t__ sparsebit_all_set (struct sparsebit*) ; 
 int /*<<< orphan*/  sparsebit_is_set (struct sparsebit*,int) ; 

__attribute__((used)) static void bit_clear(struct sparsebit *s, sparsebit_idx_t idx)
{
	struct node *nodep;

	/* Skip bits that are already cleared */
	if (!sparsebit_is_set(s, idx))
		return;

	/* Is there a node that describes the setting of this bit? */
	nodep = node_find(s, idx);
	if (!nodep)
		return;

	/*
	 * If a num_after bit, split the node, so that the bit is
	 * part of a node mask.
	 */
	if (idx >= nodep->idx + MASK_BITS)
		nodep = node_split(s, idx & -MASK_BITS);

	/*
	 * After node_split above, bit at idx should be within the mask.
	 * Clear that bit.
	 */
	assert(idx >= nodep->idx && idx <= nodep->idx + MASK_BITS - 1);
	assert(nodep->mask & (1 << (idx - nodep->idx)));
	nodep->mask &= ~(1 << (idx - nodep->idx));
	assert(s->num_set > 0 || sparsebit_all_set(s));
	s->num_set--;

	node_reduce(s, nodep);
}