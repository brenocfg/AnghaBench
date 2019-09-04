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
struct item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_sanity (struct item*,unsigned long) ; 
 struct item* radix_tree_lookup (struct radix_tree_root*,unsigned long) ; 

void item_check_present(struct radix_tree_root *root, unsigned long index)
{
	struct item *item;

	item = radix_tree_lookup(root, index);
	assert(item != NULL);
	item_sanity(item, index);
}