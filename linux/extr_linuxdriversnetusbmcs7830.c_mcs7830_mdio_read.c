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
struct net_device {int dummy; } ;

/* Variables and functions */
 int mcs7830_read_phy (struct usbnet*,int) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mcs7830_mdio_read(struct net_device *netdev, int phy_id,
			     int location)
{
	struct usbnet *dev = netdev_priv(netdev);
	return mcs7830_read_phy(dev, location);
}