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
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int DEVLINK_CMD_FLASH_UPDATE ; 
 int DEVLINK_CMD_FLASH_UPDATE_END ; 
 int DEVLINK_CMD_FLASH_UPDATE_STATUS ; 
 int /*<<< orphan*/  DEVLINK_MCGRP_CONFIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devlink_net (struct devlink*) ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 int devlink_nl_flash_update_fill (struct sk_buff*,struct devlink*,int,char const*,char const*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __devlink_flash_update_notify(struct devlink *devlink,
					  enum devlink_command cmd,
					  const char *status_msg,
					  const char *component,
					  unsigned long done,
					  unsigned long total)
{
	struct sk_buff *msg;
	int err;

	WARN_ON(cmd != DEVLINK_CMD_FLASH_UPDATE &&
		cmd != DEVLINK_CMD_FLASH_UPDATE_END &&
		cmd != DEVLINK_CMD_FLASH_UPDATE_STATUS);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return;

	err = devlink_nl_flash_update_fill(msg, devlink, cmd, status_msg,
					   component, done, total);
	if (err)
		goto out_free_msg;

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
	return;

out_free_msg:
	nlmsg_free(msg);
}