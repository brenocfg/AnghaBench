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
struct TYPE_2__ {int bEncryptionValue; int /*<<< orphan*/  bEncryptionType; } ;
struct wusb_dev {TYPE_1__ ccm1_etd; } ;
struct device {int dummy; } ;
struct usb_device {struct wusb_dev* wusb_dev; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_SET_ENCRYPTION ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wusb_et_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wusb_dev_set_encryption(struct usb_device *usb_dev, int value)
{
	int result;
	struct device *dev = &usb_dev->dev;
	struct wusb_dev *wusb_dev = usb_dev->wusb_dev;

	if (value) {
		value = wusb_dev->ccm1_etd.bEncryptionValue;
	} else {
		/* FIXME: should be wusb_dev->etd[UNSECURE].bEncryptionValue */
		value = 0;
	}
	/* Set device's */
	result = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			USB_REQ_SET_ENCRYPTION,
			USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
			value, 0, NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (result < 0)
		dev_err(dev, "Can't set device's WUSB encryption to "
			"%s (value %d): %d\n",
			wusb_et_name(wusb_dev->ccm1_etd.bEncryptionType),
			wusb_dev->ccm1_etd.bEncryptionValue,  result);
	return result;
}