#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct genl_multicast_group {int dummy; } ;
struct genl_family {int /*<<< orphan*/  netnsok; } ;
struct TYPE_3__ {int /*<<< orphan*/  genl_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  CTRL_CMD_DELFAMILY 131 
#define  CTRL_CMD_DELMCAST_GRP 130 
#define  CTRL_CMD_NEWFAMILY 129 
#define  CTRL_CMD_NEWMCAST_GRP 128 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (struct genl_multicast_group const*) ; 
 struct sk_buff* ctrl_build_family_msg (struct genl_family const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* ctrl_build_mcgrp_msg (struct genl_family const*,struct genl_multicast_group const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genl_ctrl ; 
 int /*<<< orphan*/  genlmsg_multicast_allns (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int genl_ctrl_event(int event, const struct genl_family *family,
			   const struct genl_multicast_group *grp,
			   int grp_id)
{
	struct sk_buff *msg;

	/* genl is still initialising */
	if (!init_net.genl_sock)
		return 0;

	switch (event) {
	case CTRL_CMD_NEWFAMILY:
	case CTRL_CMD_DELFAMILY:
		WARN_ON(grp);
		msg = ctrl_build_family_msg(family, 0, 0, event);
		break;
	case CTRL_CMD_NEWMCAST_GRP:
	case CTRL_CMD_DELMCAST_GRP:
		BUG_ON(!grp);
		msg = ctrl_build_mcgrp_msg(family, grp, grp_id, 0, 0, event);
		break;
	default:
		return -EINVAL;
	}

	if (IS_ERR(msg))
		return PTR_ERR(msg);

	if (!family->netnsok) {
		genlmsg_multicast_netns(&genl_ctrl, &init_net, msg, 0,
					0, GFP_KERNEL);
	} else {
		rcu_read_lock();
		genlmsg_multicast_allns(&genl_ctrl, msg, 0,
					0, GFP_ATOMIC);
		rcu_read_unlock();
	}

	return 0;
}