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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sr_share_write_word (struct usbnet*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sr_mdio_write(struct net_device *netdev, int phy_id, int loc,
			  int val)
{
	struct usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);

	if (phy_id) {
		netdev_dbg(netdev, "Only internal phy supported\n");
		return;
	}

	netdev_dbg(netdev, "sr_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
		   phy_id, loc, val);

	sr_share_write_word(dev, 1, loc, res);
}