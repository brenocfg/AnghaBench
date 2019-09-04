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
 int /*<<< orphan*/  item_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int item_tag_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_tag_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extend_checks(void)
{
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert(&tree, 43);
	assert(item_tag_get(&tree, 43, 0) == 0);
	item_tag_set(&tree, 43, 0);
	assert(item_tag_get(&tree, 43, 0) == 1);
	item_insert(&tree, 1000000);
	assert(item_tag_get(&tree, 43, 0) == 1);

	item_insert(&tree, 0);
	item_tag_set(&tree, 0, 0);
	item_delete(&tree, 1000000);
	assert(item_tag_get(&tree, 43, 0) != 0);
	item_delete(&tree, 43);
	assert(item_tag_get(&tree, 43, 0) == 0);	/* crash */
	assert(item_tag_get(&tree, 0, 0) == 1);

	verify_tag_consistency(&tree, 0);

	item_kill_tree(&tree);
}