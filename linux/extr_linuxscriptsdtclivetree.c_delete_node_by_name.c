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
struct node {struct node* next_sibling; int /*<<< orphan*/  name; struct node* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_node (struct node*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 

void delete_node_by_name(struct node *parent, char *name)
{
	struct node *node = parent->children;

	while (node) {
		if (streq(node->name, name)) {
			delete_node(node);
			return;
		}
		node = node->next_sibling;
	}
}