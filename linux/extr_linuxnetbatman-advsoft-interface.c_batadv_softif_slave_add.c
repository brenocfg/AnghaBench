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
struct net_device {int /*<<< orphan*/  name; } ;
struct net {int dummy; } ;
struct batadv_hard_iface {scalar_t__ soft_iface; } ;

/* Variables and functions */
 int EINVAL ; 
 int batadv_hardif_enable_interface (struct batadv_hard_iface*,struct net*,int /*<<< orphan*/ ) ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct net* dev_net (struct net_device*) ; 

__attribute__((used)) static int batadv_softif_slave_add(struct net_device *dev,
				   struct net_device *slave_dev,
				   struct netlink_ext_ack *extack)
{
	struct batadv_hard_iface *hard_iface;
	struct net *net = dev_net(dev);
	int ret = -EINVAL;

	hard_iface = batadv_hardif_get_by_netdev(slave_dev);
	if (!hard_iface || hard_iface->soft_iface)
		goto out;

	ret = batadv_hardif_enable_interface(hard_iface, net, dev->name);

out:
	if (hard_iface)
		batadv_hardif_put(hard_iface);
	return ret;
}