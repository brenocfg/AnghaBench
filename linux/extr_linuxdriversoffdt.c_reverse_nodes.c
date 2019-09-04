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
struct device_node {struct device_node* child; struct device_node* sibling; } ;

/* Variables and functions */

__attribute__((used)) static void reverse_nodes(struct device_node *parent)
{
	struct device_node *child, *next;

	/* In-depth first */
	child = parent->child;
	while (child) {
		reverse_nodes(child);

		child = child->sibling;
	}

	/* Reverse the nodes in the child list */
	child = parent->child;
	parent->child = NULL;
	while (child) {
		next = child->sibling;

		child->sibling = parent->child;
		parent->child = child;
		child = next;
	}
}