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
struct sk_buff {int dummy; } ;
struct genl_info {struct devlink** user_ptr; } ;
struct devlink {int /*<<< orphan*/  param_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_PARAM_NEW ; 
 int __devlink_nl_cmd_param_set_doit (struct devlink*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct genl_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_param_set_doit(struct sk_buff *skb,
					 struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];

	return __devlink_nl_cmd_param_set_doit(devlink, 0, &devlink->param_list,
					       info, DEVLINK_CMD_PARAM_NEW);
}