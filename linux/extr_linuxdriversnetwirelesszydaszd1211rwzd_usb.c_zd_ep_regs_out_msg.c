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
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP_REGS_OUT ; 
 int usb_bulk_msg (struct usb_device*,unsigned int,void*,int,int*,int) ; 
 scalar_t__ usb_endpoint_xfer_int (int /*<<< orphan*/ *) ; 
 int usb_interrupt_msg (struct usb_device*,unsigned int,void*,int,int*,int) ; 
 struct usb_host_endpoint* usb_pipe_endpoint (struct usb_device*,unsigned int) ; 
 unsigned int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd_ep_regs_out_msg(struct usb_device *udev, void *data, int len,
			      int *actual_length, int timeout)
{
	/* In USB 2.0 mode EP_REGS_OUT endpoint is interrupt type. However in
	 * USB 1.1 mode endpoint is bulk. Select correct type URB by endpoint
	 * descriptor.
	 */
	struct usb_host_endpoint *ep;
	unsigned int pipe;

	pipe = usb_sndintpipe(udev, EP_REGS_OUT);
	ep = usb_pipe_endpoint(udev, pipe);
	if (!ep)
		return -EINVAL;

	if (usb_endpoint_xfer_int(&ep->desc)) {
		return usb_interrupt_msg(udev, pipe, data, len,
					 actual_length, timeout);
	} else {
		pipe = usb_sndbulkpipe(udev, EP_REGS_OUT);
		return usb_bulk_msg(udev, pipe, data, len, actual_length,
				    timeout);
	}
}