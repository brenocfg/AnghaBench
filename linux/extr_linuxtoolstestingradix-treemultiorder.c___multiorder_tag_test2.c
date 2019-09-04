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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ item_insert (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ item_insert_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int radix_tree_tag_set (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int tag_tagged_items (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void __multiorder_tag_test2(unsigned order, unsigned long index2)
{
	RADIX_TREE(tree, GFP_KERNEL);
	unsigned long index = (1 << order);
	index2 += index;

	assert(item_insert_order(&tree, 0, order) == 0);
	assert(item_insert(&tree, index2) == 0);

	assert(radix_tree_tag_set(&tree, 0, 0));
	assert(radix_tree_tag_set(&tree, index2, 0));

	assert(tag_tagged_items(&tree, NULL, 0, ~0UL, 10, 0, 1) == 2);

	item_kill_tree(&tree);
}