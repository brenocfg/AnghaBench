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
 int /*<<< orphan*/  abort () ; 
 unsigned long find_item (struct radix_tree_root*,struct item*) ; 
 int /*<<< orphan*/  item_insert_order (struct radix_tree_root*,unsigned long,unsigned int) ; 
 struct item* item_lookup (struct radix_tree_root*,unsigned long) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,unsigned int,unsigned long) ; 

__attribute__((used)) static void __locate_check(struct radix_tree_root *tree, unsigned long index,
			unsigned order)
{
	struct item *item;
	unsigned long index2;

	item_insert_order(tree, index, order);
	item = item_lookup(tree, index);
	index2 = find_item(tree, item);
	if (index != index2) {
		printv(2, "index %ld order %d inserted; found %ld\n",
			index, order, index2);
		abort();
	}
}