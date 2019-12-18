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
struct devlink_trap_group_item {int /*<<< orphan*/  refcount; } ;
struct devlink_trap_group {int /*<<< orphan*/  name; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct devlink_trap_group_item* devlink_trap_group_item_create (struct devlink*,struct devlink_trap_group const*) ; 
 struct devlink_trap_group_item* devlink_trap_group_item_lookup (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct devlink_trap_group_item *
devlink_trap_group_item_get(struct devlink *devlink,
			    const struct devlink_trap_group *group)
{
	struct devlink_trap_group_item *group_item;

	group_item = devlink_trap_group_item_lookup(devlink, group->name);
	if (group_item) {
		refcount_inc(&group_item->refcount);
		return group_item;
	}

	return devlink_trap_group_item_create(devlink, group);
}