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
struct urb {int transfer_buffer_length; int actual_length; int transfer_flags; int transfer_buffer; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_STAGE ; 
 int URB_ZERO_PACKET ; 
 int USB_PID_IN ; 
 int USB_PID_OUT ; 
 int c67x00_create_td (struct c67x00_hcd*,struct urb*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int usb_gettoggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int usb_maxpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ usb_pipecontrol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c67x00_add_data_urb(struct c67x00_hcd *c67x00, struct urb *urb)
{
	int remaining;
	int toggle;
	int pid;
	int ret = 0;
	int maxps;
	int need_empty;

	toggle = usb_gettoggle(urb->dev, usb_pipeendpoint(urb->pipe),
			       usb_pipeout(urb->pipe));
	remaining = urb->transfer_buffer_length - urb->actual_length;

	maxps = usb_maxpacket(urb->dev, urb->pipe, usb_pipeout(urb->pipe));

	need_empty = (urb->transfer_flags & URB_ZERO_PACKET) &&
	    usb_pipeout(urb->pipe) && !(remaining % maxps);

	while (remaining || need_empty) {
		int len;
		char *td_buf;

		len = (remaining > maxps) ? maxps : remaining;
		if (!len)
			need_empty = 0;

		pid = usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;
		td_buf = urb->transfer_buffer + urb->transfer_buffer_length -
		    remaining;
		ret = c67x00_create_td(c67x00, urb, td_buf, len, pid, toggle,
				       DATA_STAGE);
		if (ret)
			return ret;	/* td wasn't created */

		toggle ^= 1;
		remaining -= len;
		if (usb_pipecontrol(urb->pipe))
			break;
	}

	return 0;
}