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
 int /*<<< orphan*/  item_check_absent (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  item_check_present (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  item_full_scan (int /*<<< orphan*/ *,unsigned long,long,int) ; 
 int /*<<< orphan*/  item_gang_check_present (int /*<<< orphan*/ *,unsigned long,long,int,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree ; 

void __gang_check(unsigned long middle, long down, long up, int chunk, int hop)
{
	long idx;
	RADIX_TREE(tree, GFP_KERNEL);

	middle = 1 << 30;

	for (idx = -down; idx < up; idx++)
		item_insert(&tree, middle + idx);

	item_check_absent(&tree, middle - down - 1);
	for (idx = -down; idx < up; idx++)
		item_check_present(&tree, middle + idx);
	item_check_absent(&tree, middle + up);

	if (chunk > 0) {
		item_gang_check_present(&tree, middle - down, up + down,
				chunk, hop);
		item_full_scan(&tree, middle - down, down + up, chunk);
	}
	item_kill_tree(&tree);
}