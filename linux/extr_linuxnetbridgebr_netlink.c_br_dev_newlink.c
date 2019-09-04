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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 size_t IFLA_ADDRESS ; 
 int br_changelink (struct net_device*,struct nlattr**,struct nlattr**,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  br_dev_delete (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_stp_change_bridge_id (struct net_bridge*,int /*<<< orphan*/ ) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_dev_newlink(struct net *src_net, struct net_device *dev,
			  struct nlattr *tb[], struct nlattr *data[],
			  struct netlink_ext_ack *extack)
{
	struct net_bridge *br = netdev_priv(dev);
	int err;

	err = register_netdevice(dev);
	if (err)
		return err;

	if (tb[IFLA_ADDRESS]) {
		spin_lock_bh(&br->lock);
		br_stp_change_bridge_id(br, nla_data(tb[IFLA_ADDRESS]));
		spin_unlock_bh(&br->lock);
	}

	err = br_changelink(dev, tb, data, extack);
	if (err)
		br_dev_delete(dev, NULL);

	return err;
}