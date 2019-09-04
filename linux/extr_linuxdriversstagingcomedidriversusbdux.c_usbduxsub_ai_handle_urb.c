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
typedef  int /*<<< orphan*/  u16 ;
struct usbdux_private {scalar_t__ ai_counter; scalar_t__ ai_timer; int /*<<< orphan*/ * in_buf; } ;
struct urb {int /*<<< orphan*/  dev; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbdux_private* private; } ;
struct comedi_cmd {int chanlist_len; scalar_t__ stop_src; scalar_t__ stop_arg; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {scalar_t__ scans_done; int events; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int COMEDI_CB_CANCEL_MASK ; 
 int COMEDI_CB_EOA ; 
 int COMEDI_CB_ERROR ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EL2NSYNC ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TRIG_COUNT ; 
 int /*<<< orphan*/  comedi_buf_write_samples (struct comedi_subdevice*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  comedi_offset_munge (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbduxsub_ai_handle_urb(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct urb *urb)
{
	struct usbdux_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	int ret;
	int i;

	devpriv->ai_counter--;
	if (devpriv->ai_counter == 0) {
		devpriv->ai_counter = devpriv->ai_timer;

		/* get the data from the USB bus and hand it over to comedi */
		for (i = 0; i < cmd->chanlist_len; i++) {
			unsigned int range = CR_RANGE(cmd->chanlist[i]);
			u16 val = le16_to_cpu(devpriv->in_buf[i]);

			/* bipolar data is two's-complement */
			if (comedi_range_is_bipolar(s, range))
				val = comedi_offset_munge(s, val);

			/* transfer data */
			if (!comedi_buf_write_samples(s, &val, 1))
				return;
		}

		if (cmd->stop_src == TRIG_COUNT &&
		    async->scans_done >= cmd->stop_arg)
			async->events |= COMEDI_CB_EOA;
	}

	/* if command is still running, resubmit urb */
	if (!(async->events & COMEDI_CB_CANCEL_MASK)) {
		urb->dev = comedi_to_usb_dev(dev);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		if (ret < 0) {
			dev_err(dev->class_dev,
				"urb resubmit failed in int-context! err=%d\n",
				ret);
			if (ret == -EL2NSYNC)
				dev_err(dev->class_dev,
					"buggy USB host controller or bug in IRQ handler!\n");
			async->events |= COMEDI_CB_ERROR;
		}
	}
}