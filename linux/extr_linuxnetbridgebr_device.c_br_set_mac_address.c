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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct net_bridge {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  br_stp_change_bridge_id (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_set_mac_address(struct net_device *dev, void *p)
{
	struct net_bridge *br = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	spin_lock_bh(&br->lock);
	if (!ether_addr_equal(dev->dev_addr, addr->sa_data)) {
		/* Mac address will be changed in br_stp_change_bridge_id(). */
		br_stp_change_bridge_id(br, addr->sa_data);
	}
	spin_unlock_bh(&br->lock);

	return 0;
}