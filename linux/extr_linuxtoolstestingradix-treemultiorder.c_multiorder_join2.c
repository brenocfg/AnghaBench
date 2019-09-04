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
struct radix_tree_node {int exceptional; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* __radix_tree_lookup (int /*<<< orphan*/ *,int,struct radix_tree_node**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* item_create (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  item_insert_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  radix_tree_join (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,void*) ; 
 void* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void multiorder_join2(unsigned order1, unsigned order2)
{
	RADIX_TREE(tree, GFP_KERNEL);
	struct radix_tree_node *node;
	void *item1 = item_create(0, order1);
	void *item2;

	item_insert_order(&tree, 0, order2);
	radix_tree_insert(&tree, 1 << order2, (void *)0x12UL);
	item2 = __radix_tree_lookup(&tree, 1 << order2, &node, NULL);
	assert(item2 == (void *)0x12UL);
	assert(node->exceptional == 1);

	item2 = radix_tree_lookup(&tree, 0);
	free(item2);

	radix_tree_join(&tree, 0, order1, item1);
	item2 = __radix_tree_lookup(&tree, 1 << order2, &node, NULL);
	assert(item2 == item1);
	assert(node->exceptional == 0);
	item_kill_tree(&tree);
}