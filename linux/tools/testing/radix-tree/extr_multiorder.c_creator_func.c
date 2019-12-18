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
struct radix_tree_root {int dummy; } ;

/* Variables and functions */
 int RADIX_TREE_MAP_SHIFT ; 
 int /*<<< orphan*/  item_delete_rcu (struct radix_tree_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_insert_order (struct radix_tree_root*,int /*<<< orphan*/ ,unsigned int) ; 
 int stop_iteration ; 

__attribute__((used)) static void *creator_func(void *ptr)
{
	/* 'order' is set up to ensure we have sibling entries */
	unsigned int order = RADIX_TREE_MAP_SHIFT - 1;
	struct radix_tree_root *tree = ptr;
	int i;

	for (i = 0; i < 10000; i++) {
		item_insert_order(tree, 0, order);
		item_delete_rcu(tree, 0);
	}

	stop_iteration = true;
	return NULL;
}