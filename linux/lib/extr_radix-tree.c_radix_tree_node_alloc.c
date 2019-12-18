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
struct radix_tree_root {int dummy; } ;
struct radix_tree_preload {scalar_t__ nr; struct radix_tree_node* nodes; } ;
struct radix_tree_node {unsigned int shift; unsigned int offset; unsigned int count; unsigned int nr_values; struct radix_tree_root* array; struct radix_tree_node* parent; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 struct radix_tree_node* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmemleak_update_trace (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (struct radix_tree_node*) ; 
 int /*<<< orphan*/  radix_tree_node_cachep ; 
 int /*<<< orphan*/  radix_tree_preloads ; 
 struct radix_tree_preload* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct radix_tree_node *
radix_tree_node_alloc(gfp_t gfp_mask, struct radix_tree_node *parent,
			struct radix_tree_root *root,
			unsigned int shift, unsigned int offset,
			unsigned int count, unsigned int nr_values)
{
	struct radix_tree_node *ret = NULL;

	/*
	 * Preload code isn't irq safe and it doesn't make sense to use
	 * preloading during an interrupt anyway as all the allocations have
	 * to be atomic. So just do normal allocation when in interrupt.
	 */
	if (!gfpflags_allow_blocking(gfp_mask) && !in_interrupt()) {
		struct radix_tree_preload *rtp;

		/*
		 * Even if the caller has preloaded, try to allocate from the
		 * cache first for the new node to get accounted to the memory
		 * cgroup.
		 */
		ret = kmem_cache_alloc(radix_tree_node_cachep,
				       gfp_mask | __GFP_NOWARN);
		if (ret)
			goto out;

		/*
		 * Provided the caller has preloaded here, we will always
		 * succeed in getting a node here (and never reach
		 * kmem_cache_alloc)
		 */
		rtp = this_cpu_ptr(&radix_tree_preloads);
		if (rtp->nr) {
			ret = rtp->nodes;
			rtp->nodes = ret->parent;
			rtp->nr--;
		}
		/*
		 * Update the allocation stack trace as this is more useful
		 * for debugging.
		 */
		kmemleak_update_trace(ret);
		goto out;
	}
	ret = kmem_cache_alloc(radix_tree_node_cachep, gfp_mask);
out:
	BUG_ON(radix_tree_is_internal_node(ret));
	if (ret) {
		ret->shift = shift;
		ret->offset = offset;
		ret->count = count;
		ret->nr_values = nr_values;
		ret->parent = parent;
		ret->array = root;
	}
	return ret;
}