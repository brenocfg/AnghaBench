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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 unsigned long RADIX_TREE_MAP_SHIFT ; 
 unsigned long RADIX_TREE_MAP_SIZE ; 
 int RADIX_TREE_MAX_PATH ; 
 int __radix_tree_preload (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 unsigned long* height_to_maxnodes ; 
 int /*<<< orphan*/  preempt_disable () ; 

int radix_tree_maybe_preload_order(gfp_t gfp_mask, int order)
{
	unsigned long nr_subtrees;
	int nr_nodes, subtree_height;

	/* Preloading doesn't help anything with this gfp mask, skip it */
	if (!gfpflags_allow_blocking(gfp_mask)) {
		preempt_disable();
		return 0;
	}

	/*
	 * Calculate number and height of fully populated subtrees it takes to
	 * store (1 << order) elements.
	 */
	nr_subtrees = 1 << order;
	for (subtree_height = 0; nr_subtrees > RADIX_TREE_MAP_SIZE;
			subtree_height++)
		nr_subtrees >>= RADIX_TREE_MAP_SHIFT;

	/*
	 * The worst case is zero height tree with a single item at index 0 and
	 * then inserting items starting at ULONG_MAX - (1 << order).
	 *
	 * This requires RADIX_TREE_MAX_PATH nodes to build branch from root to
	 * 0-index item.
	 */
	nr_nodes = RADIX_TREE_MAX_PATH;

	/* Plus branch to fully populated subtrees. */
	nr_nodes += RADIX_TREE_MAX_PATH - subtree_height;

	/* Root node is shared. */
	nr_nodes--;

	/* Plus nodes required to build subtrees. */
	nr_nodes += nr_subtrees * height_to_maxnodes[subtree_height];

	return __radix_tree_preload(gfp_mask, nr_nodes);
}