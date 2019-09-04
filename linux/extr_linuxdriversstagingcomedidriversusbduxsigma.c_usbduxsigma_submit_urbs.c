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
struct usb_device {int dummy; } ;
struct urb {int interval; int /*<<< orphan*/  transfer_flags; scalar_t__ status; struct usb_device* dev; struct comedi_device* context; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbduxsigma_submit_urbs(struct comedi_device *dev,
				   struct urb **urbs, int num_urbs,
				   int input_urb)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct urb *urb;
	int ret;
	int i;

	/* Submit all URBs and start the transfer on the bus */
	for (i = 0; i < num_urbs; i++) {
		urb = urbs[i];

		/* in case of a resubmission after an unlink... */
		if (input_urb)
			urb->interval = 1;
		urb->context = dev;
		urb->dev = usb;
		urb->status = 0;
		urb->transfer_flags = URB_ISO_ASAP;

		ret = usb_submit_urb(urb, GFP_ATOMIC);
		if (ret)
			return ret;
	}
	return 0;
}