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
 int /*<<< orphan*/  __locate_check (int /*<<< orphan*/ *,int,unsigned int) ; 
 int /*<<< orphan*/  __order_0_locate_check () ; 
 int /*<<< orphan*/  abort () ; 
 int find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void locate_check(void)
{
	RADIX_TREE(tree, GFP_KERNEL);
	unsigned order;
	unsigned long offset, index;

	__order_0_locate_check();

	for (order = 0; order < 20; order++) {
		for (offset = 0; offset < (1 << (order + 3));
		     offset += (1UL << order)) {
			for (index = 0; index < (1UL << (order + 5));
			     index += (1UL << order)) {
				__locate_check(&tree, index + offset, order);
			}
			if (find_item(&tree, &tree) != -1)
				abort();

			item_kill_tree(&tree);
		}
	}

	if (find_item(&tree, &tree) != -1)
		abort();
	__locate_check(&tree, -1, 0);
	if (find_item(&tree, &tree) != -1)
		abort();
	item_kill_tree(&tree);
}