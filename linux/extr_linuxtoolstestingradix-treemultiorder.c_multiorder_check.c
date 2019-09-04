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
struct item {unsigned long index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  item_check_absent (int /*<<< orphan*/ *,unsigned long) ; 
 struct item* item_create (unsigned long,int) ; 
 scalar_t__ item_delete (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ item_insert_order (int /*<<< orphan*/ *,unsigned long,int) ; 
 struct item* item_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,int) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,unsigned long,struct item*) ; 
 void** radix_tree_lookup_slot (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  radix_tree_replace_slot (int /*<<< orphan*/ *,void**,struct item*) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void multiorder_check(unsigned long index, int order)
{
	unsigned long i;
	unsigned long min = index & ~((1UL << order) - 1);
	unsigned long max = min + (1UL << order);
	void **slot;
	struct item *item2 = item_create(min, order);
	RADIX_TREE(tree, GFP_KERNEL);

	printv(2, "Multiorder index %ld, order %d\n", index, order);

	assert(item_insert_order(&tree, index, order) == 0);

	for (i = min; i < max; i++) {
		struct item *item = item_lookup(&tree, i);
		assert(item != 0);
		assert(item->index == index);
	}
	for (i = 0; i < min; i++)
		item_check_absent(&tree, i);
	for (i = max; i < 2*max; i++)
		item_check_absent(&tree, i);
	for (i = min; i < max; i++)
		assert(radix_tree_insert(&tree, i, item2) == -EEXIST);

	slot = radix_tree_lookup_slot(&tree, index);
	free(*slot);
	radix_tree_replace_slot(&tree, slot, item2);
	for (i = min; i < max; i++) {
		struct item *item = item_lookup(&tree, i);
		assert(item != 0);
		assert(item->index == min);
	}

	assert(item_delete(&tree, min) != 0);

	for (i = 0; i < 2*max; i++)
		item_check_absent(&tree, i);
}