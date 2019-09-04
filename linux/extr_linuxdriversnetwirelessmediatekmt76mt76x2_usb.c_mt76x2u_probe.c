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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  dev; } ;
struct mt76x2_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MT_ASIC_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mt76_hw (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x2_dev*,int /*<<< orphan*/ ) ; 
 int mt76u_init (TYPE_1__*,struct usb_interface*) ; 
 struct mt76x2_dev* mt76x2u_alloc_device (int /*<<< orphan*/ *) ; 
 int mt76x2u_register_device (struct mt76x2_dev*) ; 
 struct usb_device* usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt76x2u_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct mt76x2_dev *dev;
	int err;

	dev = mt76x2u_alloc_device(&intf->dev);
	if (!dev)
		return -ENOMEM;

	udev = usb_get_dev(udev);
	usb_reset_device(udev);

	err = mt76u_init(&dev->mt76, intf);
	if (err < 0)
		goto err;

	dev->mt76.rev = mt76_rr(dev, MT_ASIC_VERSION);
	dev_info(dev->mt76.dev, "ASIC revision: %08x\n", dev->mt76.rev);

	err = mt76x2u_register_device(dev);
	if (err < 0)
		goto err;

	return 0;

err:
	ieee80211_free_hw(mt76_hw(dev));
	usb_set_intfdata(intf, NULL);
	usb_put_dev(udev);

	return err;
}