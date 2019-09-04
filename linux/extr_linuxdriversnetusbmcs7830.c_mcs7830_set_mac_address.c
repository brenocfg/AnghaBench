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
struct usbnet {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EBUSY ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int mcs7830_hif_set_mac_address (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int mcs7830_set_mac_address(struct net_device *netdev, void *p)
{
	int ret;
	struct usbnet *dev = netdev_priv(netdev);
	struct sockaddr *addr = p;

	if (netif_running(netdev))
		return -EBUSY;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	ret = mcs7830_hif_set_mac_address(dev, addr->sa_data);

	if (ret < 0)
		return ret;

	/* it worked --> adopt it on netdev side */
	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);

	return 0;
}