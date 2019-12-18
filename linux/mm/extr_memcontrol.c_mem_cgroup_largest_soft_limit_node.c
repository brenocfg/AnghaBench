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
struct mem_cgroup_tree_per_node {int /*<<< orphan*/  lock; } ;
struct mem_cgroup_per_node {int dummy; } ;

/* Variables and functions */
 struct mem_cgroup_per_node* __mem_cgroup_largest_soft_limit_node (struct mem_cgroup_tree_per_node*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mem_cgroup_per_node *
mem_cgroup_largest_soft_limit_node(struct mem_cgroup_tree_per_node *mctz)
{
	struct mem_cgroup_per_node *mz;

	spin_lock_irq(&mctz->lock);
	mz = __mem_cgroup_largest_soft_limit_node(mctz);
	spin_unlock_irq(&mctz->lock);
	return mz;
}