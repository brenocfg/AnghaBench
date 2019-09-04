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
struct net_device {scalar_t__* dev_addr; int /*<<< orphan*/  mtu; } ;
struct net_dev_context {int is_mamac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_DATA_LEN ; 
 int /*<<< orphan*/  MAMAC_DATA_LEN ; 
 int eth_mac_addr (struct net_device*,void*) ; 
 struct net_dev_context* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int most_nd_set_mac_address(struct net_device *dev, void *p)
{
	struct net_dev_context *nd = netdev_priv(dev);
	int err = eth_mac_addr(dev, p);

	if (err)
		return err;

	nd->is_mamac =
		(dev->dev_addr[0] == 0 && dev->dev_addr[1] == 0 &&
		 dev->dev_addr[2] == 0 && dev->dev_addr[3] == 0);

	/*
	 * Set default MTU for the given packet type.
	 * It is still possible to change MTU using ip tools afterwards.
	 */
	dev->mtu = nd->is_mamac ? MAMAC_DATA_LEN : ETH_DATA_LEN;

	return 0;
}