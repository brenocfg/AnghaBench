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
struct sparsebit {struct node* root; } ;
struct node {int idx; int num_after; int mask; struct node* right; struct node* left; } ;
typedef  scalar_t__ sparsebit_idx_t ;

/* Variables and functions */
 int MASK_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ node_first_set (struct node*,scalar_t__) ; 
 struct node* node_next (struct sparsebit*,struct node*) ; 

sparsebit_idx_t sparsebit_next_set(struct sparsebit *s,
	sparsebit_idx_t prev)
{
	sparsebit_idx_t lowest_possible = prev + 1;
	sparsebit_idx_t start;
	struct node *nodep;

	/* A bit after the highest index can't be set. */
	if (lowest_possible == 0)
		return 0;

	/*
	 * Find the leftmost 'candidate' overlapping or to the right
	 * of lowest_possible.
	 */
	struct node *candidate = NULL;

	/* True iff lowest_possible is within candidate */
	bool contains = false;

	/*
	 * Find node that describes setting of bit at lowest_possible.
	 * If such a node doesn't exist, find the node with the lowest
	 * starting index that is > lowest_possible.
	 */
	for (nodep = s->root; nodep;) {
		if ((nodep->idx + MASK_BITS + nodep->num_after - 1)
			>= lowest_possible) {
			candidate = nodep;
			if (candidate->idx <= lowest_possible) {
				contains = true;
				break;
			}
			nodep = nodep->left;
		} else {
			nodep = nodep->right;
		}
	}
	if (!candidate)
		return 0;

	assert(candidate->mask != 0);

	/* Does the candidate node describe the setting of lowest_possible? */
	if (!contains) {
		/*
		 * Candidate doesn't describe setting of bit at lowest_possible.
		 * Candidate points to the first node with a starting index
		 * > lowest_possible.
		 */
		assert(candidate->idx > lowest_possible);

		return node_first_set(candidate, 0);
	}

	/*
	 * Candidate describes setting of bit at lowest_possible.
	 * Note: although the node describes the setting of the bit
	 * at lowest_possible, its possible that its setting and the
	 * setting of all latter bits described by this node are 0.
	 * For now, just handle the cases where this node describes
	 * a bit at or after an index of lowest_possible that is set.
	 */
	start = lowest_possible - candidate->idx;

	if (start < MASK_BITS && candidate->mask >= (1 << start))
		return node_first_set(candidate, start);

	if (candidate->num_after) {
		sparsebit_idx_t first_num_after_idx = candidate->idx + MASK_BITS;

		return lowest_possible < first_num_after_idx
			? first_num_after_idx : lowest_possible;
	}

	/*
	 * Although candidate node describes setting of bit at
	 * the index of lowest_possible, all bits at that index and
	 * latter that are described by candidate are cleared.  With
	 * this, the next bit is the first bit in the next node, if
	 * such a node exists.  If a next node doesn't exist, then
	 * there is no next set bit.
	 */
	candidate = node_next(s, candidate);
	if (!candidate)
		return 0;

	return node_first_set(candidate, 0);
}