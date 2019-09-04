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

/* Variables and functions */
 struct net* batadv_getlink_net (struct net_device const*,struct net*) ; 
 int dev_get_iflink (struct net_device const*) ; 
 scalar_t__ net_eq (struct net const*,struct net*) ; 

__attribute__((used)) static bool batadv_mutual_parents(const struct net_device *dev1,
				  struct net *net1,
				  const struct net_device *dev2,
				  struct net *net2)
{
	int dev1_parent_iflink = dev_get_iflink(dev1);
	int dev2_parent_iflink = dev_get_iflink(dev2);
	const struct net *dev1_parent_net;
	const struct net *dev2_parent_net;

	dev1_parent_net = batadv_getlink_net(dev1, net1);
	dev2_parent_net = batadv_getlink_net(dev2, net2);

	if (!dev1_parent_iflink || !dev2_parent_iflink)
		return false;

	return (dev1_parent_iflink == dev2->ifindex) &&
	       (dev2_parent_iflink == dev1->ifindex) &&
	       net_eq(dev1_parent_net, net2) &&
	       net_eq(dev2_parent_net, net1);
}