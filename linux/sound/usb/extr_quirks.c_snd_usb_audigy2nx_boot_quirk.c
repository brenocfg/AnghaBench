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
typedef  scalar_t__ u8 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_OTHER ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  snd_usb_ctl_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_audigy2nx_boot_quirk(struct usb_device *dev)
{
	u8 buf = 1;

	snd_usb_ctl_msg(dev, usb_rcvctrlpipe(dev, 0), 0x2a,
			USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			0, 0, &buf, 1);
	if (buf == 0) {
		snd_usb_ctl_msg(dev, usb_sndctrlpipe(dev, 0), 0x29,
				USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_OTHER,
				1, 2000, NULL, 0);
		return -ENODEV;
	}
	return 0;
}