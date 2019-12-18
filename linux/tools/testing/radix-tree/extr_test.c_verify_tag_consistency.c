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
struct radix_tree_root {struct radix_tree_node* xa_head; } ;
struct radix_tree_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radix_tree_is_internal_node (struct radix_tree_node*) ; 
 int /*<<< orphan*/  root_tag_get (struct radix_tree_root*,unsigned int) ; 
 int /*<<< orphan*/  verify_node (struct radix_tree_node*,unsigned int,int) ; 

void verify_tag_consistency(struct radix_tree_root *root, unsigned int tag)
{
	struct radix_tree_node *node = root->xa_head;
	if (!radix_tree_is_internal_node(node))
		return;
	verify_node(node, tag, !!root_tag_get(root, tag));
}