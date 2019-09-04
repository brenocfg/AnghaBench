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
struct net_device {int mtu; } ;
struct macvlan_dev {TYPE_1__* lowerdev; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_change_mtu(struct net_device *dev, int new_mtu)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	if (vlan->lowerdev->mtu < new_mtu)
		return -EINVAL;
	dev->mtu = new_mtu;
	return 0;
}