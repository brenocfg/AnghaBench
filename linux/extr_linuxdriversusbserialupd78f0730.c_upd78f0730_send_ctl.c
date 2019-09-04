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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct usb_serial_port {struct device dev; TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void const*,int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int upd78f0730_send_ctl(struct usb_serial_port *port,
			const void *data, int size)
{
	struct usb_device *usbdev = port->serial->dev;
	void *buf;
	int res;

	if (size <= 0 || !data)
		return -EINVAL;

	buf = kmemdup(data, size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	res = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0), 0x00,
			USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT,
			0x0000, 0x0000, buf, size, USB_CTRL_SET_TIMEOUT);

	kfree(buf);

	if (res != size) {
		struct device *dev = &port->dev;

		dev_err(dev, "failed to send control request %02x: %d\n",
			*(u8 *)data, res);
		/* The maximum expected length of a transfer is 6 bytes */
		if (res >= 0)
			res = -EIO;

		return res;
	}

	return 0;
}