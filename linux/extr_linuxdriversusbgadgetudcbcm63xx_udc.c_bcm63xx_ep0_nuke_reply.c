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
struct usb_request {int dummy; } ;
struct bcm63xx_udc {struct usb_request* ep0_request; scalar_t__ ep0_req_completed; int /*<<< orphan*/  gadget; struct usb_request* ep0_reply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 int /*<<< orphan*/  bcm63xx_ep0_complete (struct bcm63xx_udc*,struct usb_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,struct usb_request*,int) ; 

__attribute__((used)) static void bcm63xx_ep0_nuke_reply(struct bcm63xx_udc *udc, int is_tx)
{
	struct usb_request *req = udc->ep0_reply;

	udc->ep0_reply = NULL;
	usb_gadget_unmap_request(&udc->gadget, req, is_tx);
	if (udc->ep0_request == req) {
		udc->ep0_req_completed = 0;
		udc->ep0_request = NULL;
	}
	bcm63xx_ep0_complete(udc, req, -ESHUTDOWN);
}