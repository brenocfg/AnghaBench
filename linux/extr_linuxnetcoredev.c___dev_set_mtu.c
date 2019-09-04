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
struct net_device_ops {int (* ndo_change_mtu ) (struct net_device*,int) ;} ;
struct net_device {int mtu; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int stub1 (struct net_device*,int) ; 

int __dev_set_mtu(struct net_device *dev, int new_mtu)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if (ops->ndo_change_mtu)
		return ops->ndo_change_mtu(dev, new_mtu);

	dev->mtu = new_mtu;
	return 0;
}