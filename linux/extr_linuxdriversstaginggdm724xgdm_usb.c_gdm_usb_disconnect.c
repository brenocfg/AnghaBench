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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct phy_dev {struct phy_dev* priv_dev; } ;
struct lte_udev {struct lte_udev* priv_dev; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct phy_dev*) ; 
 int /*<<< orphan*/  release_usb (struct phy_dev*) ; 
 int /*<<< orphan*/  unregister_lte_device (struct phy_dev*) ; 
 struct phy_dev* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 

__attribute__((used)) static void gdm_usb_disconnect(struct usb_interface *intf)
{
	struct phy_dev *phy_dev;
	struct lte_udev *udev;
	struct usb_device *usbdev;

	usbdev = interface_to_usbdev(intf);
	phy_dev = usb_get_intfdata(intf);

	udev = phy_dev->priv_dev;
	unregister_lte_device(phy_dev);

	release_usb(udev);

	kfree(udev);
	udev = NULL;

	kfree(phy_dev);
	phy_dev = NULL;

	usb_put_dev(usbdev);
}