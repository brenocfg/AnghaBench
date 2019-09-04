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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct usb_device {int dummy; } ;
struct usb_ctrlrequest {int bRequestType; int /*<<< orphan*/  wLength; scalar_t__ wIndex; scalar_t__ wValue; int /*<<< orphan*/  bRequest; } ;
struct urb {int dummy; } ;
struct es2_ap_dev {struct usb_device* usb_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  ap_urb_complete ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct usb_ctrlrequest*) ; 
 struct usb_ctrlrequest* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int output_async(struct es2_ap_dev *es2, void *req, u16 size, u8 cmd)
{
	struct usb_device *udev = es2->usb_dev;
	struct urb *urb;
	struct usb_ctrlrequest *dr;
	u8 *buf;
	int retval;

	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb)
		return -ENOMEM;

	dr = kmalloc(sizeof(*dr) + size, GFP_ATOMIC);
	if (!dr) {
		usb_free_urb(urb);
		return -ENOMEM;
	}

	buf = (u8 *)dr + sizeof(*dr);
	memcpy(buf, req, size);

	dr->bRequest = cmd;
	dr->bRequestType = USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE;
	dr->wValue = 0;
	dr->wIndex = 0;
	dr->wLength = cpu_to_le16(size);

	usb_fill_control_urb(urb, udev, usb_sndctrlpipe(udev, 0),
			     (unsigned char *)dr, buf, size,
			     ap_urb_complete, dr);
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	if (retval) {
		usb_free_urb(urb);
		kfree(dr);
	}
	return retval;
}