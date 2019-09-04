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
 int INT_MAX ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __locate_check (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int rand () ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void __order_0_locate_check(void)
{
	RADIX_TREE(tree, GFP_KERNEL);
	int i;

	for (i = 0; i < 50; i++)
		__locate_check(&tree, rand() % INT_MAX, 0);

	item_kill_tree(&tree);
}