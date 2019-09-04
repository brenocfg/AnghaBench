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
struct net_device {int dummy; } ;
struct macvlan_dev {int dummy; } ;

/* Variables and functions */
 size_t macvlan_get_size_mac (struct macvlan_dev*) ; 
 struct macvlan_dev* netdev_priv (struct net_device const*) ; 
 size_t nla_total_size (int) ; 

__attribute__((used)) static size_t macvlan_get_size(const struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	return (0
		+ nla_total_size(4) /* IFLA_MACVLAN_MODE */
		+ nla_total_size(2) /* IFLA_MACVLAN_FLAGS */
		+ nla_total_size(4) /* IFLA_MACVLAN_MACADDR_COUNT */
		+ macvlan_get_size_mac(vlan) /* IFLA_MACVLAN_MACADDR */
		);
}