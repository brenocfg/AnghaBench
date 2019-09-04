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
struct net_device {int dummy; } ;
struct macvlan_dev {TYPE_1__* lowerdev; } ;
struct TYPE_2__ {int ifindex; } ;

/* Variables and functions */
 struct macvlan_dev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static int macvlan_dev_get_iflink(const struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	return vlan->lowerdev->ifindex;
}