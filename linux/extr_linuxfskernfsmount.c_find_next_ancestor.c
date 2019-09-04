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
struct kernfs_node {struct kernfs_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_crit_once (char*) ; 

__attribute__((used)) static struct kernfs_node *find_next_ancestor(struct kernfs_node *child,
					      struct kernfs_node *parent)
{
	if (child == parent) {
		pr_crit_once("BUG in find_next_ancestor: called with parent == child");
		return NULL;
	}

	while (child->parent != parent) {
		if (!child->parent)
			return NULL;
		child = child->parent;
	}

	return child;
}