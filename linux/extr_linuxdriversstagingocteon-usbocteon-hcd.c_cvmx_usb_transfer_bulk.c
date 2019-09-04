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
struct TYPE_2__ {scalar_t__ nak; } ;
union cvmx_usbcx_hcintx {TYPE_1__ s; } ;
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {scalar_t__ stage; } ;
struct cvmx_usb_pipe {int max_packet; scalar_t__ device_speed; scalar_t__ transfer_dir; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CVMX_USB_DIRECTION_OUT ; 
 int /*<<< orphan*/  CVMX_USB_PIPE_FLAGS_NEED_PING ; 
 scalar_t__ CVMX_USB_SPEED_HIGH ; 
 scalar_t__ CVMX_USB_STAGE_NON_CONTROL ; 
 scalar_t__ CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE ; 
 int /*<<< orphan*/  CVMX_USB_STATUS_OK ; 
 int /*<<< orphan*/  cvmx_usb_complete (struct octeon_hcd*,struct cvmx_usb_pipe*,struct cvmx_usb_transaction*,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_usb_pipe_needs_split (struct octeon_hcd*,struct cvmx_usb_pipe*) ; 

__attribute__((used)) static void cvmx_usb_transfer_bulk(struct octeon_hcd *usb,
				   struct cvmx_usb_pipe *pipe,
				   struct cvmx_usb_transaction *transaction,
				   union cvmx_usbcx_hcintx usbc_hcint,
				   int buffer_space_left,
				   int bytes_in_last_packet)
{
	/*
	 * The only time a bulk transfer isn't complete when it finishes with
	 * an ACK is during a split transaction. For splits we need to continue
	 * the transfer if more data is needed.
	 */
	if (cvmx_usb_pipe_needs_split(usb, pipe)) {
		if (transaction->stage == CVMX_USB_STAGE_NON_CONTROL)
			transaction->stage =
				CVMX_USB_STAGE_NON_CONTROL_SPLIT_COMPLETE;
		else if (buffer_space_left &&
			 (bytes_in_last_packet == pipe->max_packet))
			transaction->stage = CVMX_USB_STAGE_NON_CONTROL;
		else
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
	} else {
		if ((pipe->device_speed == CVMX_USB_SPEED_HIGH) &&
		    (pipe->transfer_dir == CVMX_USB_DIRECTION_OUT) &&
		    (usbc_hcint.s.nak))
			pipe->flags |= CVMX_USB_PIPE_FLAGS_NEED_PING;
		if (!buffer_space_left ||
		    (bytes_in_last_packet < pipe->max_packet))
			cvmx_usb_complete(usb, pipe, transaction,
					  CVMX_USB_STATUS_OK);
	}
}