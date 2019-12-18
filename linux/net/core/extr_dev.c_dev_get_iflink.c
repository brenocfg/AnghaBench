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
struct net_device {int ifindex; TYPE_1__* netdev_ops; } ;
struct TYPE_2__ {int (* ndo_get_iflink ) (struct net_device const*) ;} ;

/* Variables and functions */
 int stub1 (struct net_device const*) ; 

int dev_get_iflink(const struct net_device *dev)
{
	if (dev->netdev_ops && dev->netdev_ops->ndo_get_iflink)
		return dev->netdev_ops->ndo_get_iflink(dev);

	return dev->ifindex;
}