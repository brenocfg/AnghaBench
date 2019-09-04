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
 int __item_insert (struct radix_tree_root*,struct item*) ; 
 int /*<<< orphan*/  free (struct item*) ; 
 struct item* item_create (unsigned long,unsigned int) ; 

int item_insert_order(struct radix_tree_root *root, unsigned long index,
			unsigned order)
{
	struct item *item = item_create(index, order);
	int err = __item_insert(root, item);
	if (err)
		free(item);
	return err;
}