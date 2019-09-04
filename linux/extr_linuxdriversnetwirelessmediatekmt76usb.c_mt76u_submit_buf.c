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
typedef  int /*<<< orphan*/  usb_complete_t ;
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct mt76u_buf {int /*<<< orphan*/  urb; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/ * out_ep; int /*<<< orphan*/ * in_ep; } ;
struct mt76_dev {TYPE_1__ usb; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int USB_DIR_IN ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 unsigned int usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mt76u_submit_buf(struct mt76_dev *dev, int dir, int index,
		     struct mt76u_buf *buf, gfp_t gfp,
		     usb_complete_t complete_fn, void *context)
{
	struct usb_interface *intf = to_usb_interface(dev->dev);
	struct usb_device *udev = interface_to_usbdev(intf);
	unsigned int pipe;

	if (dir == USB_DIR_IN)
		pipe = usb_rcvbulkpipe(udev, dev->usb.in_ep[index]);
	else
		pipe = usb_sndbulkpipe(udev, dev->usb.out_ep[index]);

	usb_fill_bulk_urb(buf->urb, udev, pipe, NULL, buf->len,
			  complete_fn, context);

	return usb_submit_urb(buf->urb, gfp);
}