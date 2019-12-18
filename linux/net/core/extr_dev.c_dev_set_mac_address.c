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
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device_ops {int (* ndo_set_mac_address ) (struct net_device*,struct sockaddr*) ;} ;
struct net_device {scalar_t__ type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_assign_type; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NETDEV_CHANGEADDR ; 
 int /*<<< orphan*/  NET_ADDR_SET ; 
 int /*<<< orphan*/  add_device_randomness (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int dev_pre_changeaddr_notify (struct net_device*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int stub1 (struct net_device*,struct sockaddr*) ; 

int dev_set_mac_address(struct net_device *dev, struct sockaddr *sa,
			struct netlink_ext_ack *extack)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	int err;

	if (!ops->ndo_set_mac_address)
		return -EOPNOTSUPP;
	if (sa->sa_family != dev->type)
		return -EINVAL;
	if (!netif_device_present(dev))
		return -ENODEV;
	err = dev_pre_changeaddr_notify(dev, sa->sa_data, extack);
	if (err)
		return err;
	err = ops->ndo_set_mac_address(dev, sa);
	if (err)
		return err;
	dev->addr_assign_type = NET_ADDR_SET;
	call_netdevice_notifiers(NETDEV_CHANGEADDR, dev);
	add_device_randomness(dev->dev_addr, dev->addr_len);
	return 0;
}