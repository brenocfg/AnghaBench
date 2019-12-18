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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_info {int /*<<< orphan*/  extack; struct nlattr** attrs; struct devlink** user_ptr; } ;
struct devlink {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* flash_update ) (struct devlink*,char const*,char const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DEVLINK_ATTR_FLASH_UPDATE_COMPONENT ; 
 size_t DEVLINK_ATTR_FLASH_UPDATE_FILE_NAME ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 char* nla_data (struct nlattr*) ; 
 int stub1 (struct devlink*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_flash_update(struct sk_buff *skb,
				       struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	const char *file_name, *component;
	struct nlattr *nla_component;

	if (!devlink->ops->flash_update)
		return -EOPNOTSUPP;

	if (!info->attrs[DEVLINK_ATTR_FLASH_UPDATE_FILE_NAME])
		return -EINVAL;
	file_name = nla_data(info->attrs[DEVLINK_ATTR_FLASH_UPDATE_FILE_NAME]);

	nla_component = info->attrs[DEVLINK_ATTR_FLASH_UPDATE_COMPONENT];
	component = nla_component ? nla_data(nla_component) : NULL;

	return devlink->ops->flash_update(devlink, file_name, component,
					  info->extack);
}