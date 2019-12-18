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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ifcdev; struct usb_device* usbdev; } ;
struct usb_line6_podhd {int firmware_version; TYPE_1__ line6; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int LINE6_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_REQ_SET_FEATURE ; 
 int USB_TYPE_STANDARD ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int line6_read_data (TYPE_1__*,int,int*,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int podhd_dev_start(struct usb_line6_podhd *pod)
{
	int ret;
	u8 *init_bytes;
	int i;
	struct usb_device *usbdev = pod->line6.usbdev;

	init_bytes = kmalloc(8, GFP_KERNEL);
	if (!init_bytes)
		return -ENOMEM;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
					0x67, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT,
					0x11, 0,
					NULL, 0, LINE6_TIMEOUT * HZ);
	if (ret < 0) {
		dev_err(pod->line6.ifcdev, "read request failed (error %d)\n", ret);
		goto exit;
	}

	/* NOTE: looks like some kind of ping message */
	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0), 0x67,
					USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
					0x11, 0x0,
					init_bytes, 3, LINE6_TIMEOUT * HZ);
	if (ret < 0) {
		dev_err(pod->line6.ifcdev,
			"receive length failed (error %d)\n", ret);
		goto exit;
	}

	pod->firmware_version =
		(init_bytes[0] << 16) | (init_bytes[1] << 8) | (init_bytes[2] << 0);

	for (i = 0; i <= 16; i++) {
		ret = line6_read_data(&pod->line6, 0xf000 + 0x08 * i, init_bytes, 8);
		if (ret < 0)
			goto exit;
	}

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
					USB_REQ_SET_FEATURE,
					USB_TYPE_STANDARD | USB_RECIP_DEVICE | USB_DIR_OUT,
					1, 0,
					NULL, 0, LINE6_TIMEOUT * HZ);
exit:
	kfree(init_bytes);
	return ret;
}