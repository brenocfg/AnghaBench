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
 unsigned long find_item (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* item_create (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  item_insert_order (int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_join (int /*<<< orphan*/ *,unsigned long,unsigned int,void*) ; 
 void* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void multiorder_join1(unsigned long index,
				unsigned order1, unsigned order2)
{
	unsigned long loc;
	void *item, *item2 = item_create(index + 1, order1);
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert_order(&tree, index, order2);
	item = radix_tree_lookup(&tree, index);
	radix_tree_join(&tree, index + 1, order1, item2);
	loc = find_item(&tree, item);
	if (loc == -1)
		free(item);
	item = radix_tree_lookup(&tree, index + 1);
	assert(item == item2);
	item_kill_tree(&tree);
}