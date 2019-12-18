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
struct net_device {int flags; scalar_t__ type; scalar_t__ addr_len; int priv_flags; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_ALEN ; 
 int IFF_DONT_BRIDGE ; 
 int IFF_LOOPBACK ; 
 scalar_t__ hsr_port_exists (struct net_device*) ; 
 scalar_t__ is_hsr_master (struct net_device*) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 

__attribute__((used)) static int hsr_check_dev_ok(struct net_device *dev)
{
	/* Don't allow HSR on non-ethernet like devices */
	if ((dev->flags & IFF_LOOPBACK) || dev->type != ARPHRD_ETHER ||
	    dev->addr_len != ETH_ALEN) {
		netdev_info(dev, "Cannot use loopback or non-ethernet device as HSR slave.\n");
		return -EINVAL;
	}

	/* Don't allow enslaving hsr devices */
	if (is_hsr_master(dev)) {
		netdev_info(dev, "Cannot create trees of HSR devices.\n");
		return -EINVAL;
	}

	if (hsr_port_exists(dev)) {
		netdev_info(dev, "This device is already a HSR slave.\n");
		return -EINVAL;
	}

	if (is_vlan_dev(dev)) {
		netdev_info(dev, "HSR on top of VLAN is not yet supported in this driver.\n");
		return -EINVAL;
	}

	if (dev->priv_flags & IFF_DONT_BRIDGE) {
		netdev_info(dev, "This device does not support bridging.\n");
		return -EOPNOTSUPP;
	}

	/* HSR over bonded devices has not been tested, but I'm not sure it
	 * won't work...
	 */

	return 0;
}