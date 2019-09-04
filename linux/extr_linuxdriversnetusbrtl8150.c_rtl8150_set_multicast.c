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
typedef  int u16 ;
struct net_device {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  rx_creg ;
typedef  int /*<<< orphan*/  rtl8150_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RCR ; 
 int /*<<< orphan*/  async_set_registers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void rtl8150_set_multicast(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	u16 rx_creg = 0x9e;

	netif_stop_queue(netdev);
	if (netdev->flags & IFF_PROMISC) {
		rx_creg |= 0x0001;
		dev_info(&netdev->dev, "%s: promiscuous mode\n", netdev->name);
	} else if (!netdev_mc_empty(netdev) ||
		   (netdev->flags & IFF_ALLMULTI)) {
		rx_creg &= 0xfffe;
		rx_creg |= 0x0002;
		dev_dbg(&netdev->dev, "%s: allmulti set\n", netdev->name);
	} else {
		/* ~RX_MULTICAST, ~RX_PROMISCUOUS */
		rx_creg &= 0x00fc;
	}
	async_set_registers(dev, RCR, sizeof(rx_creg), rx_creg);
	netif_wake_queue(netdev);
}