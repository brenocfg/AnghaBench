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
typedef  int u8 ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;
typedef  enum devlink_trap_action { ____Placeholder_devlink_trap_action } devlink_trap_action ;

/* Variables and functions */
 size_t DEVLINK_ATTR_TRAP_ACTION ; 
#define  DEVLINK_TRAP_ACTION_DROP 129 
#define  DEVLINK_TRAP_ACTION_TRAP 128 
 int EINVAL ; 
 int nla_get_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devlink_trap_action_get_from_info(struct genl_info *info,
				  enum devlink_trap_action *p_trap_action)
{
	u8 val;

	val = nla_get_u8(info->attrs[DEVLINK_ATTR_TRAP_ACTION]);
	switch (val) {
	case DEVLINK_TRAP_ACTION_DROP: /* fall-through */
	case DEVLINK_TRAP_ACTION_TRAP:
		*p_trap_action = val;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}