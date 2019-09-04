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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct usbhsg_request {TYPE_1__ pkt; } ;
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,struct usb_request*) ; 
 struct usbhsg_request* usbhsg_req_to_ureq (struct usb_request*) ; 

__attribute__((used)) static void __usbhsg_recip_send_complete(struct usb_ep *ep,
					 struct usb_request *req)
{
	struct usbhsg_request *ureq = usbhsg_req_to_ureq(req);

	/* free allocated recip-buffer/usb_request */
	kfree(ureq->pkt.buf);
	usb_ep_free_request(ep, req);
}