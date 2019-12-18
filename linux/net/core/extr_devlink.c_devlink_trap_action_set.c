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
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;
struct devlink_trap_item {int dummy; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_trap_action { ____Placeholder_devlink_trap_action } devlink_trap_action ;

/* Variables and functions */
 size_t DEVLINK_ATTR_TRAP_ACTION ; 
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int __devlink_trap_action_set (struct devlink*,struct devlink_trap_item*,int,int /*<<< orphan*/ ) ; 
 int devlink_trap_action_get_from_info (struct genl_info*,int*) ; 

__attribute__((used)) static int devlink_trap_action_set(struct devlink *devlink,
				   struct devlink_trap_item *trap_item,
				   struct genl_info *info)
{
	enum devlink_trap_action trap_action;
	int err;

	if (!info->attrs[DEVLINK_ATTR_TRAP_ACTION])
		return 0;

	err = devlink_trap_action_get_from_info(info, &trap_action);
	if (err) {
		NL_SET_ERR_MSG_MOD(info->extack, "Invalid trap action");
		return -EINVAL;
	}

	return __devlink_trap_action_set(devlink, trap_item, trap_action,
					 info->extack);
}