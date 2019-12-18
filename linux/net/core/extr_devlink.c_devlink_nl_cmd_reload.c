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
struct genl_info {int /*<<< orphan*/  extack; struct devlink** user_ptr; } ;
struct devlink {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* reload_down ) (struct devlink*,int /*<<< orphan*/ ) ;int (* reload_up ) (struct devlink*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devlink_reload_failed_set (struct devlink*,int) ; 
 int /*<<< orphan*/  devlink_reload_supported (struct devlink*) ; 
 int devlink_resources_validate (struct devlink*,int /*<<< orphan*/ *,struct genl_info*) ; 
 int stub1 (struct devlink*,int /*<<< orphan*/ ) ; 
 int stub2 (struct devlink*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devlink_nl_cmd_reload(struct sk_buff *skb, struct genl_info *info)
{
	struct devlink *devlink = info->user_ptr[0];
	int err;

	if (!devlink_reload_supported(devlink))
		return -EOPNOTSUPP;

	err = devlink_resources_validate(devlink, NULL, info);
	if (err) {
		NL_SET_ERR_MSG_MOD(info->extack, "resources size validation failed");
		return err;
	}
	err = devlink->ops->reload_down(devlink, info->extack);
	if (err)
		return err;
	err = devlink->ops->reload_up(devlink, info->extack);
	devlink_reload_failed_set(devlink, !!err);
	return err;
}