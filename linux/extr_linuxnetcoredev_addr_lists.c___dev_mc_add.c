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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_HW_ADDR_T_MULTICAST ; 
 int /*<<< orphan*/  __dev_set_rx_mode (struct net_device*) ; 
 int __hw_addr_add_ex (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 

__attribute__((used)) static int __dev_mc_add(struct net_device *dev, const unsigned char *addr,
			bool global)
{
	int err;

	netif_addr_lock_bh(dev);
	err = __hw_addr_add_ex(&dev->mc, addr, dev->addr_len,
			       NETDEV_HW_ADDR_T_MULTICAST, global, false, 0);
	if (!err)
		__dev_set_rx_mode(dev);
	netif_addr_unlock_bh(dev);
	return err;
}