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
 int /*<<< orphan*/  bit_set (struct sparsebit*,int) ; 
 struct node* node_next (struct sparsebit*,struct node*) ; 
 int /*<<< orphan*/  node_reduce (struct sparsebit*,struct node*) ; 
 int /*<<< orphan*/  node_rm (struct sparsebit*,struct node*) ; 
 struct node* node_split (struct sparsebit*,int) ; 

void sparsebit_set_num(struct sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
{
	struct node *nodep, *next;
	unsigned int n1;
	sparsebit_idx_t idx;
	sparsebit_num_t n;
	sparsebit_idx_t middle_start, middle_end;

	assert(num > 0);
	assert(start + num - 1 >= start);

	/*
	 * Leading - bits before first mask boundary.
	 *
	 * TODO(lhuemill): With some effort it may be possible to
	 *   replace the following loop with a sequential sequence
	 *   of statements.  High level sequence would be:
	 *
	 *     1. Use node_split() to force node that describes setting
	 *        of idx to be within the mask portion of a node.
	 *     2. Form mask of bits to be set.
	 *     3. Determine number of mask bits already set in the node
	 *        and store in a local variable named num_already_set.
	 *     4. Set the appropriate mask bits within the node.
	 *     5. Increment struct sparsebit_pvt num_set member
	 *        by the number of bits that were actually set.
	 *        Exclude from the counts bits that were already set.
	 *     6. Before returning to the caller, use node_reduce() to
	 *        handle the multiple corner cases that this method
	 *        introduces.
	 */
	for (idx = start, n = num; n > 0 && idx % MASK_BITS != 0; idx++, n--)
		bit_set(s, idx);

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

		/* As needed set each of the mask bits */
		for (n1 = 0; n1 < MASK_BITS; n1++) {
			if (!(nodep->mask & (1 << n1))) {
				nodep->mask |= 1 << n1;
				s->num_set++;
			}
		}

		s->num_set -= nodep->num_after;
		nodep->num_after = middle_end - middle_start + 1 - MASK_BITS;
		s->num_set += nodep->num_after;

		node_reduce(s, nodep);
	}
	idx = middle_end + 1;
	n -= middle_end - middle_start + 1;

	/* Trailing - bits at and beyond last mask boundary */
	assert(n < MASK_BITS);
	for (; n > 0; idx++, n--)
		bit_set(s, idx);
}