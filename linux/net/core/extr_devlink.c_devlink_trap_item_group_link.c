#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devlink_trap_item {struct devlink_trap_group_item* group_item; TYPE_1__* trap; } ;
struct devlink_trap_group_item {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct devlink_trap_group_item*) ; 
 int PTR_ERR (struct devlink_trap_group_item*) ; 
 struct devlink_trap_group_item* devlink_trap_group_item_get (struct devlink*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devlink_trap_item_group_link(struct devlink *devlink,
			     struct devlink_trap_item *trap_item)
{
	struct devlink_trap_group_item *group_item;

	group_item = devlink_trap_group_item_get(devlink,
						 &trap_item->trap->group);
	if (IS_ERR(group_item))
		return PTR_ERR(group_item);

	trap_item->group_item = group_item;

	return 0;
}