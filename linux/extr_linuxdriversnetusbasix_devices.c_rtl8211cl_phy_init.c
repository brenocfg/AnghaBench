#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct usbnet {TYPE_1__ mii; int /*<<< orphan*/  net; int /*<<< orphan*/  data; } ;
struct asix_data {int ledmode; } ;

/* Variables and functions */
 int asix_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asix_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rtl8211cl_phy_init(struct usbnet *dev)
{
	struct asix_data *data = (struct asix_data *)&dev->data;

	netdev_dbg(dev->net, "rtl8211cl_phy_init()\n");

	asix_mdio_write (dev->net, dev->mii.phy_id, 0x1f, 0x0005);
	asix_mdio_write (dev->net, dev->mii.phy_id, 0x0c, 0);
	asix_mdio_write (dev->net, dev->mii.phy_id, 0x01,
		asix_mdio_read (dev->net, dev->mii.phy_id, 0x01) | 0x0080);
	asix_mdio_write (dev->net, dev->mii.phy_id, 0x1f, 0);

	if (data->ledmode == 12) {
		asix_mdio_write (dev->net, dev->mii.phy_id, 0x1f, 0x0002);
		asix_mdio_write (dev->net, dev->mii.phy_id, 0x1a, 0x00cb);
		asix_mdio_write (dev->net, dev->mii.phy_id, 0x1f, 0);
	}

	return 0;
}