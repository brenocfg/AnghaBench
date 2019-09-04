#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct radix_tree_node {int dummy; } ;
struct item {scalar_t__ index; } ;
struct TYPE_8__ {struct radix_tree_node* rnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  item_check_absent (TYPE_1__*,unsigned long) ; 
 scalar_t__ item_delete (TYPE_1__*,unsigned long) ; 
 scalar_t__ item_insert (TYPE_1__*,unsigned long) ; 
 scalar_t__ item_insert_order (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct item* item_lookup (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,int) ; 
 TYPE_1__ tree ; 

__attribute__((used)) static void multiorder_shrink(unsigned long index, int order)
{
	unsigned long i;
	unsigned long max = 1 << order;
	RADIX_TREE(tree, GFP_KERNEL);
	struct radix_tree_node *node;

	printv(2, "Multiorder shrink index %ld, order %d\n", index, order);

	assert(item_insert_order(&tree, 0, order) == 0);

	node = tree.rnode;

	assert(item_insert(&tree, index) == 0);
	assert(node != tree.rnode);

	assert(item_delete(&tree, index) != 0);
	assert(node == tree.rnode);

	for (i = 0; i < max; i++) {
		struct item *item = item_lookup(&tree, i);
		assert(item != 0);
		assert(item->index == 0);
	}
	for (i = max; i < 2*max; i++)
		item_check_absent(&tree, i);

	if (!item_delete(&tree, 0)) {
		printv(2, "failed to delete index %ld (order %d)\n", index, order);
		abort();
	}

	for (i = 0; i < 2*max; i++)
		item_check_absent(&tree, i);
}