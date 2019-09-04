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
struct net_device {int /*<<< orphan*/  name; } ;
struct ks_wlan_private {int /*<<< orphan*/  mac_address_valid; scalar_t__ cur_rx; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 

__attribute__((used)) static
int ks_wlan_open(struct net_device *dev)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	priv->cur_rx = 0;

	if (!priv->mac_address_valid) {
		netdev_err(dev, "ks_wlan : %s Not READY !!\n", dev->name);
		return -EBUSY;
	}
	netif_start_queue(dev);

	return 0;
}