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
struct sparsebit {int num_set; } ;
struct node {int idx; int num_after; int mask; } ;
typedef  int sparsebit_num_t ;
typedef  int sparsebit_idx_t ;

/* Variables and functions */
 int MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bit_clear (struct sparsebit*,int) ; 
 struct node* node_next (struct sparsebit*,struct node*) ; 
 int /*<<< orphan*/  node_reduce (struct sparsebit*,struct node*) ; 
 int /*<<< orphan*/  node_rm (struct sparsebit*,struct node*) ; 
 struct node* node_split (struct sparsebit*,int) ; 

void sparsebit_clear_num(struct sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
{
	struct node *nodep, *next;
	unsigned int n1;
	sparsebit_idx_t idx;
	sparsebit_num_t n;
	sparsebit_idx_t middle_start, middle_end;

	assert(num > 0);
	assert(start + num - 1 >= start);

	/* Leading - bits before first mask boundary */
	for (idx = start, n = num; n > 0 && idx % MASK_BITS != 0; idx++, n--)
		bit_clear(s, idx);

	/* Middle - bits spanning one or more entire mask */
	middle_start = idx;
	middle_end = middle_start + (n & -MASK_BITS) - 1;
	if (n >= MASK_BITS) {
		nodep = node_split(s, middle_start);

		/*
		 * As needed, split just after end of middle bits.
		 * No split needed if end of middle bits is at highest
		 * supported bit index.
		 */
		if (middle_end + 1 > middle_end)
			(void) node_split(s, middle_end + 1);

		/* Delete nodes that only describe bits within the middle. */
		for (next = node_next(s, nodep);
			next && (next->idx < middle_end);
			next = node_next(s, nodep)) {
			assert(next->idx + MASK_BITS + next->num_after - 1 <= middle_end);
			node_rm(s, next);
			next = NULL;
		}

		/* As needed clear each of the mask bits */
		for (n1 = 0; n1 < MASK_BITS; n1++) {
			if (nodep->mask & (1 << n1)) {
				nodep->mask &= ~(1 << n1);
				s->num_set--;
			}
		}

		/* Clear any bits described by num_after */
		s->num_set -= nodep->num_after;
		nodep->num_after = 0;

		/*
		 * Delete the node that describes the beginning of
		 * the middle bits and perform any allowed reductions
		 * with the nodes prev or next of nodep.
		 */
		node_reduce(s, nodep);
		nodep = NULL;
	}
	idx = middle_end + 1;
	n -= middle_end - middle_start + 1;

	/* Trailing - bits at and beyond last mask boundary */
	assert(n < MASK_BITS);
	for (; n > 0; idx++, n--)
		bit_clear(s, idx);
}