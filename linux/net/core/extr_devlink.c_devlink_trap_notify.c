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
struct devlink_trap_item {int dummy; } ;
struct devlink {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;

/* Variables and functions */
 int DEVLINK_CMD_TRAP_DEL ; 
 int DEVLINK_CMD_TRAP_NEW ; 
 int /*<<< orphan*/  DEVLINK_MCGRP_CONFIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  devlink_net (struct devlink*) ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 int devlink_nl_trap_fill (struct sk_buff*,struct devlink*,struct devlink_trap_item const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devlink_trap_notify(struct devlink *devlink,
				const struct devlink_trap_item *trap_item,
				enum devlink_command cmd)
{
	struct sk_buff *msg;
	int err;

	WARN_ON_ONCE(cmd != DEVLINK_CMD_TRAP_NEW &&
		     cmd != DEVLINK_CMD_TRAP_DEL);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return;

	err = devlink_nl_trap_fill(msg, devlink, trap_item, cmd, 0, 0, 0);
	if (err) {
		nlmsg_free(msg);
		return;
	}

	genlmsg_multicast_netns(&devlink_nl_family, devlink_net(devlink),
				msg, 0, DEVLINK_MCGRP_CONFIG, GFP_KERNEL);
}