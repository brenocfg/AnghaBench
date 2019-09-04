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
 int /*<<< orphan*/  CONTROL_TIMEOUT_MS ; 
 int ENODEV ; 
 int /*<<< orphan*/  REQUEST_READ ; 
 int /*<<< orphan*/  control_read (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ch9200_mdio_read(struct net_device *netdev, int phy_id, int loc)
{
	struct usbnet *dev = netdev_priv(netdev);
	unsigned char buff[2];

	netdev_dbg(netdev, "ch9200_mdio_read phy_id:%02x loc:%02x\n",
		   phy_id, loc);

	if (phy_id != 0)
		return -ENODEV;

	control_read(dev, REQUEST_READ, 0, loc * 2, buff, 0x02,
		     CONTROL_TIMEOUT_MS);

	return (buff[0] | buff[1] << 8);
}