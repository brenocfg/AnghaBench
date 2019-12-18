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
 int /*<<< orphan*/  __simple_checks (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  printv (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int) ; 

void simple_checks(void)
{
	unsigned long index;
	RADIX_TREE(tree, GFP_KERNEL);

	for (index = 0; index < 10000; index++) {
		__simple_checks(&tree, index, 0);
		__simple_checks(&tree, index, 1);
	}
	verify_tag_consistency(&tree, 0);
	verify_tag_consistency(&tree, 1);
	printv(2, "before item_kill_tree: %d allocated\n", nr_allocated);
	item_kill_tree(&tree);
	rcu_barrier();
	printv(2, "after item_kill_tree: %d allocated\n", nr_allocated);
}