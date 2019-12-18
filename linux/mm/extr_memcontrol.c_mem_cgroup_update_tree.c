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
struct page {int dummy; } ;
struct mem_cgroup_tree_per_node {int /*<<< orphan*/  lock; } ;
struct mem_cgroup_per_node {scalar_t__ on_tree; } ;
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_insert_exceeded (struct mem_cgroup_per_node*,struct mem_cgroup_tree_per_node*,unsigned long) ; 
 int /*<<< orphan*/  __mem_cgroup_remove_exceeded (struct mem_cgroup_per_node*,struct mem_cgroup_tree_per_node*) ; 
 struct mem_cgroup_per_node* mem_cgroup_page_nodeinfo (struct mem_cgroup*,struct page*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 unsigned long soft_limit_excess (struct mem_cgroup*) ; 
 struct mem_cgroup_tree_per_node* soft_limit_tree_from_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mem_cgroup_update_tree(struct mem_cgroup *memcg, struct page *page)
{
	unsigned long excess;
	struct mem_cgroup_per_node *mz;
	struct mem_cgroup_tree_per_node *mctz;

	mctz = soft_limit_tree_from_page(page);
	if (!mctz)
		return;
	/*
	 * Necessary to update all ancestors when hierarchy is used.
	 * because their event counter is not touched.
	 */
	for (; memcg; memcg = parent_mem_cgroup(memcg)) {
		mz = mem_cgroup_page_nodeinfo(memcg, page);
		excess = soft_limit_excess(memcg);
		/*
		 * We have to update the tree if mz is on RB-tree or
		 * mem is over its softlimit.
		 */
		if (excess || mz->on_tree) {
			unsigned long flags;

			spin_lock_irqsave(&mctz->lock, flags);
			/* if on-tree, remove it */
			if (mz->on_tree)
				__mem_cgroup_remove_exceeded(mz, mctz);
			/*
			 * Insert again. mz->usage_in_excess will be updated.
			 * If excess is 0, no tree ops.
			 */
			__mem_cgroup_insert_exceeded(mz, mctz, excess);
			spin_unlock_irqrestore(&mctz->lock, flags);
		}
	}
}