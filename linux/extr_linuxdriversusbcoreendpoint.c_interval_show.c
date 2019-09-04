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
struct ep_device {TYPE_1__* udev; TYPE_2__* desc; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {unsigned int bEndpointAddress; unsigned int bInterval; } ;
struct TYPE_3__ {scalar_t__ speed; } ;

/* Variables and functions */
 unsigned int USB_DIR_IN ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,char) ; 
 struct ep_device* to_ep_device (struct device*) ; 
 int usb_endpoint_type (TYPE_2__*) ; 

__attribute__((used)) static ssize_t interval_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct ep_device *ep = to_ep_device(dev);
	char unit;
	unsigned interval = 0;
	unsigned in;

	in = (ep->desc->bEndpointAddress & USB_DIR_IN);

	switch (usb_endpoint_type(ep->desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		if (ep->udev->speed == USB_SPEED_HIGH)
			/* uframes per NAK */
			interval = ep->desc->bInterval;
		break;

	case USB_ENDPOINT_XFER_ISOC:
		interval = 1 << (ep->desc->bInterval - 1);
		break;

	case USB_ENDPOINT_XFER_BULK:
		if (ep->udev->speed == USB_SPEED_HIGH && !in)
			/* uframes per NAK */
			interval = ep->desc->bInterval;
		break;

	case USB_ENDPOINT_XFER_INT:
		if (ep->udev->speed == USB_SPEED_HIGH)
			interval = 1 << (ep->desc->bInterval - 1);
		else
			interval = ep->desc->bInterval;
		break;
	}
	interval *= (ep->udev->speed == USB_SPEED_HIGH) ? 125 : 1000;
	if (interval % 1000)
		unit = 'u';
	else {
		unit = 'm';
		interval /= 1000;
	}

	return sprintf(buf, "%d%cs\n", interval, unit);
}