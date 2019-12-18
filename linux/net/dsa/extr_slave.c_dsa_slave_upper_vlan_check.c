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
struct netlink_ext_ack {int dummy; } ;
struct netdev_notifier_changeupper_info {scalar_t__ linking; int /*<<< orphan*/  upper_dev; int /*<<< orphan*/  info; } ;
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  bridge_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int NOTIFY_DONE ; 
 scalar_t__ br_vlan_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_slave_dev_check (struct net_device*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  is_vlan_dev (struct net_device*) ; 
 struct netlink_ext_ack* netdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_is_bridge_master (int /*<<< orphan*/ ) ; 
 int notifier_from_errno (int /*<<< orphan*/ ) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static int dsa_slave_upper_vlan_check(struct net_device *dev,
				      struct netdev_notifier_changeupper_info *
				      info)
{
	struct netlink_ext_ack *ext_ack;
	struct net_device *slave;
	struct dsa_port *dp;

	ext_ack = netdev_notifier_info_to_extack(&info->info);

	if (!is_vlan_dev(dev))
		return NOTIFY_DONE;

	slave = vlan_dev_real_dev(dev);
	if (!dsa_slave_dev_check(slave))
		return NOTIFY_DONE;

	dp = dsa_slave_to_port(slave);
	if (!dp->bridge_dev)
		return NOTIFY_DONE;

	/* Deny enslaving a VLAN device into a VLAN-aware bridge */
	if (br_vlan_enabled(dp->bridge_dev) &&
	    netif_is_bridge_master(info->upper_dev) && info->linking) {
		NL_SET_ERR_MSG_MOD(ext_ack,
				   "Cannot enslave VLAN device into VLAN aware bridge");
		return notifier_from_errno(-EINVAL);
	}

	return NOTIFY_DONE;
}