#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usbnet {int /*<<< orphan*/  net; TYPE_2__* udev; } ;
struct TYPE_4__ {int /*<<< orphan*/  devpath; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_name; } ;

/* Variables and functions */
 int MK_TTL (int,int /*<<< orphan*/ ) ; 
 int NC_READ_TTL_MS ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  REG_TTL ; 
 int /*<<< orphan*/  REG_USBCTL ; 
 int STATUS_CONN_OTHER ; 
 int STATUS_PORT_A ; 
 int /*<<< orphan*/  TTL_OTHER (int) ; 
 int USBCTL_FLUSH_OTHER ; 
 int USBCTL_FLUSH_THIS ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  nc_dump_status (struct usbnet*,int) ; 
 int /*<<< orphan*/  nc_dump_usbctl (struct usbnet*,int) ; 
 int nc_register_read (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nc_register_write (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  netif_info (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char,char*) ; 

__attribute__((used)) static int net1080_reset(struct usbnet *dev)
{
	u16		usbctl, status, ttl;
	u16		vp;
	int		retval;

	// nc_dump_registers(dev);

	if ((retval = nc_register_read(dev, REG_STATUS, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read %s-%s status: %d\n",
			   dev->udev->bus->bus_name, dev->udev->devpath, retval);
		goto done;
	}
	status = vp;
	nc_dump_status(dev, status);

	if ((retval = nc_register_read(dev, REG_USBCTL, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read USBCTL, %d\n", retval);
		goto done;
	}
	usbctl = vp;
	nc_dump_usbctl(dev, usbctl);

	nc_register_write(dev, REG_USBCTL,
			USBCTL_FLUSH_THIS | USBCTL_FLUSH_OTHER);

	if ((retval = nc_register_read(dev, REG_TTL, &vp)) < 0) {
		netdev_dbg(dev->net, "can't read TTL, %d\n", retval);
		goto done;
	}
	ttl = vp;

	nc_register_write(dev, REG_TTL,
			MK_TTL(NC_READ_TTL_MS, TTL_OTHER(ttl)) );
	netdev_dbg(dev->net, "assigned TTL, %d ms\n", NC_READ_TTL_MS);

	netif_info(dev, link, dev->net, "port %c, peer %sconnected\n",
		   (status & STATUS_PORT_A) ? 'A' : 'B',
		   (status & STATUS_CONN_OTHER) ? "" : "dis");
	retval = 0;

done:
	return retval;
}