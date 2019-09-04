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
 int /*<<< orphan*/  item_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  printv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void __leak_check(void)
{
	RADIX_TREE(tree, GFP_KERNEL);

	printv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_insert(&tree, 1000000);
	printv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_delete(&tree, 1000000);
	printv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
	item_kill_tree(&tree);
	printv(2, "%d: nr_allocated=%d\n", __LINE__, nr_allocated);
}