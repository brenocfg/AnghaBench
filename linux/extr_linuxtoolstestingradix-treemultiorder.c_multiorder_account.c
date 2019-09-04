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
struct radix_tree_node {int count; int exceptional; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __radix_tree_insert (int /*<<< orphan*/ *,int,int,void*) ; 
 int /*<<< orphan*/  __radix_tree_lookup (int /*<<< orphan*/ *,int,struct radix_tree_node**,void***) ; 
 int /*<<< orphan*/  __radix_tree_replace (int /*<<< orphan*/ *,struct radix_tree_node*,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  item_insert_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void multiorder_account(void)
{
	RADIX_TREE(tree, GFP_KERNEL);
	struct radix_tree_node *node;
	void **slot;

	item_insert_order(&tree, 0, 5);

	__radix_tree_insert(&tree, 1 << 5, 5, (void *)0x12);
	__radix_tree_lookup(&tree, 0, &node, NULL);
	assert(node->count == node->exceptional * 2);
	radix_tree_delete(&tree, 1 << 5);
	assert(node->exceptional == 0);

	__radix_tree_insert(&tree, 1 << 5, 5, (void *)0x12);
	__radix_tree_lookup(&tree, 1 << 5, &node, &slot);
	assert(node->count == node->exceptional * 2);
	__radix_tree_replace(&tree, node, slot, NULL, NULL);
	assert(node->exceptional == 0);

	item_kill_tree(&tree);
}