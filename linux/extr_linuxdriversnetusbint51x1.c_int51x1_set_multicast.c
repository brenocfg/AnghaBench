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
struct usbnet {int /*<<< orphan*/  net; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int PACKET_TYPE_ALL_MULTICAST ; 
 int PACKET_TYPE_BROADCAST ; 
 int PACKET_TYPE_DIRECTED ; 
 int PACKET_TYPE_PROMISCUOUS ; 
 int /*<<< orphan*/  SET_ETHERNET_PACKET_FILTER ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usbnet_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void int51x1_set_multicast(struct net_device *netdev)
{
	struct usbnet *dev = netdev_priv(netdev);
	u16 filter = PACKET_TYPE_DIRECTED | PACKET_TYPE_BROADCAST;

	if (netdev->flags & IFF_PROMISC) {
		/* do not expect to see traffic of other PLCs */
		filter |= PACKET_TYPE_PROMISCUOUS;
		netdev_info(dev->net, "promiscuous mode enabled\n");
	} else if (!netdev_mc_empty(netdev) ||
		  (netdev->flags & IFF_ALLMULTI)) {
		filter |= PACKET_TYPE_ALL_MULTICAST;
		netdev_dbg(dev->net, "receive all multicast enabled\n");
	} else {
		/* ~PROMISCUOUS, ~MULTICAST */
		netdev_dbg(dev->net, "receive own packets only\n");
	}

	usbnet_write_cmd_async(dev, SET_ETHERNET_PACKET_FILTER,
			       USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
			       filter, 0, NULL, 0);
}