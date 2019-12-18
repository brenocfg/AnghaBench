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
struct item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RADIX_TREE_MAP_SHIFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  item_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_tag_clear (int /*<<< orphan*/ *,int,int) ; 
 int item_tag_get (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  item_tag_set (int /*<<< orphan*/ *,int,int) ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void contract_checks(void)
{
	struct item *item;
	int tmp;
	RADIX_TREE(tree, GFP_KERNEL);

	tmp = 1<<RADIX_TREE_MAP_SHIFT;
	item_insert(&tree, tmp);
	item_insert(&tree, tmp+1);
	item_tag_set(&tree, tmp, 0);
	item_tag_set(&tree, tmp, 1);
	item_tag_set(&tree, tmp+1, 0);
	item_delete(&tree, tmp+1);
	item_tag_clear(&tree, tmp, 1);

	assert(radix_tree_gang_lookup_tag(&tree, (void **)&item, 0, 1, 0) == 1);
	assert(radix_tree_gang_lookup_tag(&tree, (void **)&item, 0, 1, 1) == 0);

	assert(item_tag_get(&tree, tmp, 0) == 1);
	assert(item_tag_get(&tree, tmp, 1) == 0);

	verify_tag_consistency(&tree, 0);
	item_kill_tree(&tree);
}