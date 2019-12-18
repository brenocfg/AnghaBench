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
 int BATCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_MARK_0 ; 
 int /*<<< orphan*/  XA_MARK_1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_tag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_tag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radix_tree_gang_lookup_tag (int /*<<< orphan*/ *,void**,int,int,int) ; 
 int tag_tagged_items (int /*<<< orphan*/ *,unsigned long,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void single_check(void)
{
	struct item *items[BATCH];
	RADIX_TREE(tree, GFP_KERNEL);
	int ret;
	unsigned long first = 0;

	item_insert(&tree, 0);
	item_tag_set(&tree, 0, 0);
	ret = radix_tree_gang_lookup_tag(&tree, (void **)items, 0, BATCH, 0);
	assert(ret == 1);
	ret = radix_tree_gang_lookup_tag(&tree, (void **)items, 1, BATCH, 0);
	assert(ret == 0);
	verify_tag_consistency(&tree, 0);
	verify_tag_consistency(&tree, 1);
	ret = tag_tagged_items(&tree, first, 10, 10, XA_MARK_0, XA_MARK_1);
	assert(ret == 1);
	ret = radix_tree_gang_lookup_tag(&tree, (void **)items, 0, BATCH, 1);
	assert(ret == 1);
	item_tag_clear(&tree, 0, 0);
	ret = radix_tree_gang_lookup_tag(&tree, (void **)items, 0, BATCH, 0);
	assert(ret == 0);
	item_kill_tree(&tree);
}