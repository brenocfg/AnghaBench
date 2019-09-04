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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree_verify_min_height (int /*<<< orphan*/ *,int) ; 

void dynamic_height_check(void)
{
	int i;
	RADIX_TREE(tree, GFP_KERNEL);
	tree_verify_min_height(&tree, 0);

	item_insert(&tree, 42);
	tree_verify_min_height(&tree, 42);

	item_insert(&tree, 1000000);
	tree_verify_min_height(&tree, 1000000);

	assert(item_delete(&tree, 1000000));
	tree_verify_min_height(&tree, 42);

	assert(item_delete(&tree, 42));
	tree_verify_min_height(&tree, 0);

	for (i = 0; i < 1000; i++) {
		item_insert(&tree, i);
		tree_verify_min_height(&tree, i);
	}

	i--;
	for (;;) {
		assert(item_delete(&tree, i));
		if (i == 0) {
			tree_verify_min_height(&tree, 0);
			break;
		}
		i--;
		tree_verify_min_height(&tree, i);
	}

	item_kill_tree(&tree);
}