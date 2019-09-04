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
struct urb {int number_of_packets; char* transfer_buffer; int /*<<< orphan*/  interval; TYPE_1__* iso_frame_desc; int /*<<< orphan*/  pipe; struct c67x00_urb_priv* hcpriv; } ;
struct c67x00_urb_priv {int cnt; TYPE_2__* ep_data; } ;
struct c67x00_hcd {int /*<<< orphan*/  current_frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_frame; } ;
struct TYPE_3__ {int offset; int length; int status; scalar_t__ actual_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int USB_PID_IN ; 
 int USB_PID_OUT ; 
 int c67x00_create_td (struct c67x00_hcd*,struct urb*,char*,int,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  c67x00_giveback_urb (struct c67x00_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c67x00_hcd_dev (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  frame_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int c67x00_add_iso_urb(struct c67x00_hcd *c67x00, struct urb *urb)
{
	struct c67x00_urb_priv *urbp = urb->hcpriv;

	if (frame_after_eq(c67x00->current_frame, urbp->ep_data->next_frame)) {
		char *td_buf;
		int len, pid, ret;

		BUG_ON(urbp->cnt >= urb->number_of_packets);

		td_buf = urb->transfer_buffer +
		    urb->iso_frame_desc[urbp->cnt].offset;
		len = urb->iso_frame_desc[urbp->cnt].length;
		pid = usb_pipeout(urb->pipe) ? USB_PID_OUT : USB_PID_IN;

		ret = c67x00_create_td(c67x00, urb, td_buf, len, pid, 0,
				       urbp->cnt);
		if (ret) {
			dev_dbg(c67x00_hcd_dev(c67x00), "create failed: %d\n",
				ret);
			urb->iso_frame_desc[urbp->cnt].actual_length = 0;
			urb->iso_frame_desc[urbp->cnt].status = ret;
			if (urbp->cnt + 1 == urb->number_of_packets)
				c67x00_giveback_urb(c67x00, urb, 0);
		}

		urbp->ep_data->next_frame =
		    frame_add(urbp->ep_data->next_frame, urb->interval);
		urbp->cnt++;
	}
	return 0;
}