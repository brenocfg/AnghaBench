#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int hard_header_len; int mtu; } ;
struct TYPE_2__ {scalar_t__ proto; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_MIN_MTU ; 
 int IP6_MAX_MTU ; 
 scalar_t__ IPPROTO_IPV6 ; 
 int IPV6_MIN_MTU ; 
 int IP_MAX_MTU ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 

int ip6_tnl_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ip6_tnl *tnl = netdev_priv(dev);

	if (tnl->parms.proto == IPPROTO_IPV6) {
		if (new_mtu < IPV6_MIN_MTU)
			return -EINVAL;
	} else {
		if (new_mtu < ETH_MIN_MTU)
			return -EINVAL;
	}
	if (tnl->parms.proto == IPPROTO_IPV6 || tnl->parms.proto == 0) {
		if (new_mtu > IP6_MAX_MTU - dev->hard_header_len)
			return -EINVAL;
	} else {
		if (new_mtu > IP_MAX_MTU - dev->hard_header_len)
			return -EINVAL;
	}
	dev->mtu = new_mtu;
	return 0;
}