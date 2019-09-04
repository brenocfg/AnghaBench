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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int do_vrf_add_slave (struct net_device*,struct net_device*,struct netlink_ext_ack*) ; 
 scalar_t__ netif_is_l3_master (struct net_device*) ; 
 scalar_t__ netif_is_l3_slave (struct net_device*) ; 

__attribute__((used)) static int vrf_add_slave(struct net_device *dev, struct net_device *port_dev,
			 struct netlink_ext_ack *extack)
{
	if (netif_is_l3_master(port_dev)) {
		NL_SET_ERR_MSG(extack,
			       "Can not enslave an L3 master device to a VRF");
		return -EINVAL;
	}

	if (netif_is_l3_slave(port_dev))
		return -EINVAL;

	return do_vrf_add_slave(dev, port_dev, extack);
}