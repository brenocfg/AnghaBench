#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {TYPE_2__* urb_listen; int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  buffer_listen; TYPE_1__* properties; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  interval; } ;
struct TYPE_7__ {scalar_t__ actual_length; } ;
struct TYPE_6__ {int capabilities; int /*<<< orphan*/  ep_ctrl_r; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  LINE6_BUFSIZE_LISTEN ; 
 int LINE6_CAP_CONTROL_MIDI ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  line6_data_received ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_line6*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_line6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_urb_ep_type_check (TYPE_2__*) ; 

__attribute__((used)) static int line6_start_listen(struct usb_line6 *line6)
{
	int err;

	if (line6->properties->capabilities & LINE6_CAP_CONTROL_MIDI) {
		usb_fill_int_urb(line6->urb_listen, line6->usbdev,
			usb_rcvintpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_BUFSIZE_LISTEN,
			line6_data_received, line6, line6->interval);
	} else {
		usb_fill_bulk_urb(line6->urb_listen, line6->usbdev,
			usb_rcvbulkpipe(line6->usbdev, line6->properties->ep_ctrl_r),
			line6->buffer_listen, LINE6_BUFSIZE_LISTEN,
			line6_data_received, line6);
	}

	/* sanity checks of EP before actually submitting */
	if (usb_urb_ep_type_check(line6->urb_listen)) {
		dev_err(line6->ifcdev, "invalid control EP\n");
		return -EINVAL;
	}

	line6->urb_listen->actual_length = 0;
	err = usb_submit_urb(line6->urb_listen, GFP_ATOMIC);
	return err;
}