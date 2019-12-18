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
struct devlink_trap_group_item {int /*<<< orphan*/  stats; int /*<<< orphan*/  list; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_TRAP_GROUP_DEL ; 
 int /*<<< orphan*/  devlink_trap_group_notify (struct devlink*,struct devlink_trap_group_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devlink_trap_group_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devlink_trap_group_item_destroy(struct devlink *devlink,
				struct devlink_trap_group_item *group_item)
{
	devlink_trap_group_notify(devlink, group_item,
				  DEVLINK_CMD_TRAP_GROUP_DEL);
	list_del(&group_item->list);
	free_percpu(group_item->stats);
	kfree(group_item);
}