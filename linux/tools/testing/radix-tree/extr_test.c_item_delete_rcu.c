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
struct xarray {int dummy; } ;
struct item {int /*<<< orphan*/  rcu_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_free_rcu ; 
 int /*<<< orphan*/  item_sanity (struct item*,unsigned long) ; 
 struct item* xa_erase (struct xarray*,unsigned long) ; 

int item_delete_rcu(struct xarray *xa, unsigned long index)
{
	struct item *item = xa_erase(xa, index);

	if (item) {
		item_sanity(item, index);
		call_rcu(&item->rcu_head, item_free_rcu);
		return 1;
	}
	return 0;
}