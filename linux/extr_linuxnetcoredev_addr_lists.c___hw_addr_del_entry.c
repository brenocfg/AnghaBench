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
struct netdev_hw_addr_list {int /*<<< orphan*/  count; } ;
struct netdev_hw_addr {int global_use; int /*<<< orphan*/  list; scalar_t__ refcount; int /*<<< orphan*/  synced; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  kfree_rcu (struct netdev_hw_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static int __hw_addr_del_entry(struct netdev_hw_addr_list *list,
			       struct netdev_hw_addr *ha, bool global,
			       bool sync)
{
	if (global && !ha->global_use)
		return -ENOENT;

	if (sync && !ha->synced)
		return -ENOENT;

	if (global)
		ha->global_use = false;

	if (sync)
		ha->synced--;

	if (--ha->refcount)
		return 0;
	list_del_rcu(&ha->list);
	kfree_rcu(ha, rcu_head);
	list->count--;
	return 0;
}