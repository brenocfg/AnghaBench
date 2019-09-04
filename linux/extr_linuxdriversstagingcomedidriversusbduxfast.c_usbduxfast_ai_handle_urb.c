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
struct usbduxfast_private {scalar_t__ ignore; } ;
struct urb {scalar_t__ status; int /*<<< orphan*/  dev; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  actual_length; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbduxfast_private* private; } ;
struct comedi_cmd {scalar_t__ stop_src; scalar_t__ stop_arg; } ;
struct comedi_async {scalar_t__ scans_done; int events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int COMEDI_CB_CANCEL_MASK ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 unsigned int comedi_nsamples_left (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbduxfast_ai_handle_urb(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct urb *urb)
{
	struct usbduxfast_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	int ret;

	if (devpriv->ignore) {
		devpriv->ignore--;
	} else {
		unsigned int nsamples;

		nsamples = comedi_bytes_to_samples(s, urb->actual_length);
		nsamples = comedi_nsamples_left(s, nsamples);
		comedi_buf_write_samples(s, urb->transfer_buffer, nsamples);

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	}

	/* if command is still running, resubmit urb for BULK transfer */
	if (!(async->events & COMEDI_CB_CANCEL_MASK)) {
		urb->dev = comedi_to_usb_dev(dev);
		urb->status = 0;
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		if (ret < 0) {
			dev_err(dev->class_dev, "urb resubm failed: %d", ret);
			async->events |= COMEDI_CB_ERROR;
		}
	}
}