#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_6__* interrupt; TYPE_4__* udev; TYPE_3__* status; TYPE_1__* driver_info; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_12__ {scalar_t__ speed; } ;
struct TYPE_10__ {int bEndpointAddress; scalar_t__ bInterval; } ;
struct TYPE_11__ {TYPE_2__ desc; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  intr_complete ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int max (int,int) ; 
 TYPE_6__* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_6__*,TYPE_4__*,unsigned int,char*,unsigned int,int /*<<< orphan*/ ,struct usbnet*,unsigned int) ; 
 unsigned int usb_maxpacket (TYPE_4__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (unsigned int) ; 
 unsigned int usb_rcvintpipe (TYPE_4__*,int) ; 

__attribute__((used)) static int init_status (struct usbnet *dev, struct usb_interface *intf)
{
	char		*buf = NULL;
	unsigned	pipe = 0;
	unsigned	maxp;
	unsigned	period;

	if (!dev->driver_info->status)
		return 0;

	pipe = usb_rcvintpipe (dev->udev,
			dev->status->desc.bEndpointAddress
				& USB_ENDPOINT_NUMBER_MASK);
	maxp = usb_maxpacket (dev->udev, pipe, 0);

	/* avoid 1 msec chatter:  min 8 msec poll rate */
	period = max ((int) dev->status->desc.bInterval,
		(dev->udev->speed == USB_SPEED_HIGH) ? 7 : 3);

	buf = kmalloc (maxp, GFP_KERNEL);
	if (buf) {
		dev->interrupt = usb_alloc_urb (0, GFP_KERNEL);
		if (!dev->interrupt) {
			kfree (buf);
			return -ENOMEM;
		} else {
			usb_fill_int_urb(dev->interrupt, dev->udev, pipe,
				buf, maxp, intr_complete, dev, period);
			dev->interrupt->transfer_flags |= URB_FREE_BUFFER;
			dev_dbg(&intf->dev,
				"status ep%din, %d bytes period %d\n",
				usb_pipeendpoint(pipe), maxp, period);
		}
	}
	return 0;
}