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
struct usbdux_private {int /*<<< orphan*/  pwm_buf_sz; struct urb* pwm_urb; } ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_buffer; } ;
struct comedi_device {struct usbdux_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbduxsub_pwm_irq ; 

__attribute__((used)) static int usbduxsub_submit_pwm_urbs(struct comedi_device *dev)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbdux_private *devpriv = dev->private;
	struct urb *urb = devpriv->pwm_urb;

	/* in case of a resubmission after an unlink... */
	usb_fill_bulk_urb(urb, usb, usb_sndbulkpipe(usb, 4),
			  urb->transfer_buffer,
			  devpriv->pwm_buf_sz,
			  usbduxsub_pwm_irq,
			  dev);

	return usb_submit_urb(urb, GFP_ATOMIC);
}