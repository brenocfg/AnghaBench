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
struct urb {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_dma; } ;
struct octeon_hcd {int dummy; } ;
struct cvmx_usb_transaction {int dummy; } ;
struct cvmx_usb_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_TRANSFER_BULK ; 
 struct cvmx_usb_transaction* cvmx_usb_submit_transaction (struct octeon_hcd*,struct cvmx_usb_pipe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct urb*) ; 

__attribute__((used)) static struct cvmx_usb_transaction *cvmx_usb_submit_bulk(
						struct octeon_hcd *usb,
						struct cvmx_usb_pipe *pipe,
						struct urb *urb)
{
	return cvmx_usb_submit_transaction(usb, pipe, CVMX_USB_TRANSFER_BULK,
					   urb->transfer_dma,
					   urb->transfer_buffer_length,
					   0, /* control_header */
					   0, /* iso_start_frame */
					   0, /* iso_number_packets */
					   NULL, /* iso_packets */
					   urb);
}