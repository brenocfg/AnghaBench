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
struct usb_hcd {int dummy; } ;
struct urb {TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int rh_call_control (struct usb_hcd*,struct urb*) ; 
 int rh_queue_status (struct usb_hcd*,struct urb*) ; 
 scalar_t__ usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rh_urb_enqueue (struct usb_hcd *hcd, struct urb *urb)
{
	if (usb_endpoint_xfer_int(&urb->ep->desc))
		return rh_queue_status (hcd, urb);
	if (usb_endpoint_xfer_control(&urb->ep->desc))
		return rh_call_control (hcd, urb);
	return -EINVAL;
}