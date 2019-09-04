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
struct usb_ctrlrequest {int dummy; } ;
struct urb {int /*<<< orphan*/  error_count; int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; scalar_t__ setup_packet; int /*<<< orphan*/  pipe; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  status; TYPE_1__* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ PIPE_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dump_pipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dump_usb_ctrlrequest (struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usbip_dump_usb_device (TYPE_1__*) ; 

void usbip_dump_urb(struct urb *urb)
{
	struct device *dev;

	if (!urb) {
		pr_debug("urb: null pointer!!\n");
		return;
	}

	if (!urb->dev) {
		pr_debug("urb->dev: null pointer!!\n");
		return;
	}

	dev = &urb->dev->dev;

	usbip_dump_usb_device(urb->dev);

	dev_dbg(dev, "   pipe                  :%08x ", urb->pipe);

	usbip_dump_pipe(urb->pipe);

	dev_dbg(dev, "   status                :%d\n", urb->status);
	dev_dbg(dev, "   transfer_flags        :%08X\n", urb->transfer_flags);
	dev_dbg(dev, "   transfer_buffer_length:%d\n",
						urb->transfer_buffer_length);
	dev_dbg(dev, "   actual_length         :%d\n", urb->actual_length);

	if (urb->setup_packet && usb_pipetype(urb->pipe) == PIPE_CONTROL)
		usbip_dump_usb_ctrlrequest(
			(struct usb_ctrlrequest *)urb->setup_packet);

	dev_dbg(dev, "   start_frame           :%d\n", urb->start_frame);
	dev_dbg(dev, "   number_of_packets     :%d\n", urb->number_of_packets);
	dev_dbg(dev, "   interval              :%d\n", urb->interval);
	dev_dbg(dev, "   error_count           :%d\n", urb->error_count);
}