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
struct sparsebit {int /*<<< orphan*/  num_set; } ;
struct node {int idx; int mask; } ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  node_reduce (struct sparsebit*,struct node*) ; 
 struct node* node_split (struct sparsebit*,int) ; 
 scalar_t__ sparsebit_is_set (struct sparsebit*,int) ; 

__attribute__((used)) static void bit_set(struct sparsebit *s, sparsebit_idx_t idx)
{
	struct node *nodep;

	/* Skip bits that are already set */
	if (sparsebit_is_set(s, idx))
		return;

	/*
	 * Get a node where the bit at idx is described by the mask.
	 * The node_split will also create a node, if there isn't
	 * already a node that describes the setting of bit.
	 */
	nodep = node_split(s, idx & -MASK_BITS);

	/* Set the bit within the nodes mask */
	assert(idx >= nodep->idx && idx <= nodep->idx + MASK_BITS - 1);
	assert(!(nodep->mask & (1 << (idx - nodep->idx))));
	nodep->mask |= 1 << (idx - nodep->idx);
	s->num_set++;

	node_reduce(s, nodep);
}