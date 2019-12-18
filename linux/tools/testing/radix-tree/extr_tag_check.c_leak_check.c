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
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void leak_check(void)
{
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert(&tree, 1000000);
	item_delete(&tree, 1000000);
	item_kill_tree(&tree);
}