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
struct item {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct item*) ; 
 struct item* item_create (unsigned long,int /*<<< orphan*/ ) ; 
 int radix_tree_insert (struct radix_tree_root*,int /*<<< orphan*/ ,struct item*) ; 

int item_insert(struct radix_tree_root *root, unsigned long index)
{
	struct item *item = item_create(index, 0);
	int err = radix_tree_insert(root, item->index, item);
	if (err)
		free(item);
	return err;
}