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
struct netdev_phys_item_id {int dummy; } ;
struct net_device_ops {int (* ndo_get_phys_port_id ) (struct net_device*,struct netdev_phys_item_id*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct net_device*,struct netdev_phys_item_id*) ; 

int dev_get_phys_port_id(struct net_device *dev,
			 struct netdev_phys_item_id *ppid)
{
	const struct net_device_ops *ops = dev->netdev_ops;

	if (!ops->ndo_get_phys_port_id)
		return -EOPNOTSUPP;
	return ops->ndo_get_phys_port_id(dev, ppid);
}