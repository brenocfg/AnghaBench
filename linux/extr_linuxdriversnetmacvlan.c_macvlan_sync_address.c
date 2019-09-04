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
struct net_device {int flags; unsigned char* dev_addr; } ;
struct macvlan_port {unsigned char* perm_addr; } ;
struct macvlan_dev {struct macvlan_port* port; struct net_device* lowerdev; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int IFF_UP ; 
 int dev_uc_add (struct net_device*,unsigned char*) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,unsigned char*) ; 
 int /*<<< orphan*/  ether_addr_copy (unsigned char*,unsigned char*) ; 
 scalar_t__ macvlan_addr_busy (struct macvlan_port*,unsigned char*) ; 
 int /*<<< orphan*/  macvlan_addr_change (struct macvlan_port*) ; 
 int /*<<< orphan*/  macvlan_clear_addr_change (struct macvlan_port*) ; 
 int /*<<< orphan*/  macvlan_hash_change_addr (struct macvlan_dev*,unsigned char*) ; 
 scalar_t__ macvlan_passthru (struct macvlan_port*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_sync_address(struct net_device *dev, unsigned char *addr)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct net_device *lowerdev = vlan->lowerdev;
	struct macvlan_port *port = vlan->port;
	int err;

	if (!(dev->flags & IFF_UP)) {
		/* Just copy in the new address */
		ether_addr_copy(dev->dev_addr, addr);
	} else {
		/* Rehash and update the device filters */
		if (macvlan_addr_busy(vlan->port, addr))
			return -EADDRINUSE;

		if (!macvlan_passthru(port)) {
			err = dev_uc_add(lowerdev, addr);
			if (err)
				return err;

			dev_uc_del(lowerdev, dev->dev_addr);
		}

		macvlan_hash_change_addr(vlan, addr);
	}
	if (macvlan_passthru(port) && !macvlan_addr_change(port)) {
		/* Since addr_change isn't set, we are here due to lower
		 * device change.  Save the lower-dev address so we can
		 * restore it later.
		 */
		ether_addr_copy(vlan->port->perm_addr,
				lowerdev->dev_addr);
	}
	macvlan_clear_addr_change(port);
	return 0;
}