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
struct text_node {scalar_t__ leaf; int /*<<< orphan*/  str; struct text_node* next; struct text_node* first_subnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct text_node*) ; 
 int /*<<< orphan*/  dstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_leaf_destroy (scalar_t__) ; 

__attribute__((used)) static void text_node_destroy(struct text_node *node)
{
	struct text_node *subnode;

	if (!node)
		return;

	subnode = node->first_subnode;
	while (subnode) {
		struct text_node *destroy_node = subnode;

		subnode = subnode->next;
		text_node_destroy(destroy_node);
	}

	dstr_free(&node->str);
	if (node->leaf)
		text_leaf_destroy(node->leaf);
	bfree(node);
}