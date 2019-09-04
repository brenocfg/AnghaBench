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
struct usbip_usb_device {int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  speed; int /*<<< orphan*/  devnum; int /*<<< orphan*/  busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbip_net_pack_uint16_t (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbip_net_pack_uint32_t (int,int /*<<< orphan*/ *) ; 

void usbip_net_pack_usb_device(int pack, struct usbip_usb_device *udev)
{
	usbip_net_pack_uint32_t(pack, &udev->busnum);
	usbip_net_pack_uint32_t(pack, &udev->devnum);
	usbip_net_pack_uint32_t(pack, &udev->speed);

	usbip_net_pack_uint16_t(pack, &udev->idVendor);
	usbip_net_pack_uint16_t(pack, &udev->idProduct);
	usbip_net_pack_uint16_t(pack, &udev->bcdDevice);
}