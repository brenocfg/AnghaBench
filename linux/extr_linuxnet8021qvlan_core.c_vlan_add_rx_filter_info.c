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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {TYPE_1__* netdev_ops; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int (* ndo_vlan_rx_add_vid ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_hw_filter_capable (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlan_add_rx_filter_info(struct net_device *dev, __be16 proto, u16 vid)
{
	if (!vlan_hw_filter_capable(dev, proto))
		return 0;

	if (netif_device_present(dev))
		return dev->netdev_ops->ndo_vlan_rx_add_vid(dev, proto, vid);
	else
		return -ENODEV;
}