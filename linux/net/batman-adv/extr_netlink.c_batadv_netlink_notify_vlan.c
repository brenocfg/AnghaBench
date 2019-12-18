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
struct batadv_softif_vlan {int dummy; } ;
struct batadv_priv {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CMD_SET_VLAN ; 
 int /*<<< orphan*/  BATADV_NL_MCGRP_CONFIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  batadv_netlink_family ; 
 int batadv_netlink_vlan_fill (struct sk_buff*,struct batadv_priv*,struct batadv_softif_vlan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int batadv_netlink_notify_vlan(struct batadv_priv *bat_priv,
			       struct batadv_softif_vlan *vlan)
{
	struct sk_buff *msg;
	int ret;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	ret = batadv_netlink_vlan_fill(msg, bat_priv, vlan,
				       BATADV_CMD_SET_VLAN, 0, 0, 0);
	if (ret < 0) {
		nlmsg_free(msg);
		return ret;
	}

	genlmsg_multicast_netns(&batadv_netlink_family,
				dev_net(bat_priv->soft_iface), msg, 0,
				BATADV_NL_MCGRP_CONFIG, GFP_KERNEL);

	return 0;
}