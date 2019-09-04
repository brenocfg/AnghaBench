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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  bLength; } ;
struct TYPE_3__ {TYPE_2__ descr; } ;
struct wusbhc {TYPE_1__ gtk; int /*<<< orphan*/  gtk_index; } ;
struct wusb_dev {struct usb_device* usb_dev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_DT_KEY ; 
 int USB_RECIP_DEVICE ; 
 int /*<<< orphan*/  USB_REQ_SET_DESCRIPTOR ; 
 int USB_TYPE_STANDARD ; 
 int /*<<< orphan*/  WUSB_KEY_INDEX_ORIGINATOR_HOST ; 
 int /*<<< orphan*/  WUSB_KEY_INDEX_TYPE_GTK ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int wusb_key_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wusb_dev_set_gtk(struct wusbhc *wusbhc, struct wusb_dev *wusb_dev)
{
	struct usb_device *usb_dev = wusb_dev->usb_dev;
	u8 key_index = wusb_key_index(wusbhc->gtk_index,
		WUSB_KEY_INDEX_TYPE_GTK, WUSB_KEY_INDEX_ORIGINATOR_HOST);

	return usb_control_msg(
		usb_dev, usb_sndctrlpipe(usb_dev, 0),
		USB_REQ_SET_DESCRIPTOR,
		USB_DIR_OUT | USB_TYPE_STANDARD | USB_RECIP_DEVICE,
		USB_DT_KEY << 8 | key_index, 0,
		&wusbhc->gtk.descr, wusbhc->gtk.descr.bLength,
		USB_CTRL_SET_TIMEOUT);
}