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
struct radix_tree_node {int dummy; } ;
typedef  int /*<<< orphan*/  radix_tree_update_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  delete_node (struct radix_tree_root*,struct radix_tree_node*,int /*<<< orphan*/ ) ; 

void __radix_tree_delete_node(struct radix_tree_root *root,
			      struct radix_tree_node *node,
			      radix_tree_update_node_t update_node)
{
	delete_node(root, node, update_node);
}