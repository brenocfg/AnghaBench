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
struct net_device {int ifindex; } ;
struct net {int dummy; } ;
struct batadv_hard_iface {int /*<<< orphan*/  soft_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 struct net* batadv_getlink_net (struct net_device*,struct net*) ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int dev_get_iflink (struct net_device*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *batadv_get_real_netdevice(struct net_device *netdev)
{
	struct batadv_hard_iface *hard_iface = NULL;
	struct net_device *real_netdev = NULL;
	struct net *real_net;
	struct net *net;
	int ifindex;

	ASSERT_RTNL();

	if (!netdev)
		return NULL;

	if (netdev->ifindex == dev_get_iflink(netdev)) {
		dev_hold(netdev);
		return netdev;
	}

	hard_iface = batadv_hardif_get_by_netdev(netdev);
	if (!hard_iface || !hard_iface->soft_iface)
		goto out;

	net = dev_net(hard_iface->soft_iface);
	ifindex = dev_get_iflink(netdev);
	real_net = batadv_getlink_net(netdev, net);
	real_netdev = dev_get_by_index(real_net, ifindex);

out:
	if (hard_iface)
		batadv_hardif_put(hard_iface);
	return real_netdev;
}