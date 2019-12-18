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
struct mem_cgroup_tree_per_node {int /*<<< orphan*/  rb_root; int /*<<< orphan*/ * rb_rightmost; } ;
struct mem_cgroup_per_node {int on_tree; int /*<<< orphan*/  tree_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rb_prev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __mem_cgroup_remove_exceeded(struct mem_cgroup_per_node *mz,
					 struct mem_cgroup_tree_per_node *mctz)
{
	if (!mz->on_tree)
		return;

	if (&mz->tree_node == mctz->rb_rightmost)
		mctz->rb_rightmost = rb_prev(&mz->tree_node);

	rb_erase(&mz->tree_node, &mctz->rb_root);
	mz->on_tree = false;
}