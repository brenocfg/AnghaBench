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
struct usb_request {scalar_t__ status; int /*<<< orphan*/  (* complete ) (struct usb_ep*,struct usb_request*) ;} ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_LED_EVENT_GADGET ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  trace_usb_gadget_giveback_request (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_led_activity (int /*<<< orphan*/ ) ; 

void usb_gadget_giveback_request(struct usb_ep *ep,
		struct usb_request *req)
{
	if (likely(req->status == 0))
		usb_led_activity(USB_LED_EVENT_GADGET);

	trace_usb_gadget_giveback_request(ep, req, 0);

	req->complete(ep, req);
}