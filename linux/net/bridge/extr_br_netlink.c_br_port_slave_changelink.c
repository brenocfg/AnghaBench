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

/* Variables and functions */
 int /*<<< orphan*/  br_port_get_rtnl (struct net_device*) ; 
 int br_setport (int /*<<< orphan*/ ,struct nlattr**) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_port_slave_changelink(struct net_device *brdev,
				    struct net_device *dev,
				    struct nlattr *tb[],
				    struct nlattr *data[],
				    struct netlink_ext_ack *extack)
{
	struct net_bridge *br = netdev_priv(brdev);
	int ret;

	if (!data)
		return 0;

	spin_lock_bh(&br->lock);
	ret = br_setport(br_port_get_rtnl(dev), data);
	spin_unlock_bh(&br->lock);

	return ret;
}