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
struct usbhsg_uep {int /*<<< orphan*/  lock; } ;
struct usbhsg_request {int dummy; } ;
struct usbhs_pipe {int dummy; } ;
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usbhs_pkt_pop (struct usbhs_pipe*,int /*<<< orphan*/ ) ; 
 struct usbhsg_uep* usbhsg_ep_to_uep (struct usb_ep*) ; 
 int /*<<< orphan*/  usbhsg_queue_pop (struct usbhsg_uep*,struct usbhsg_request*,int /*<<< orphan*/ ) ; 
 struct usbhsg_request* usbhsg_req_to_ureq (struct usb_request*) ; 
 struct usbhs_pipe* usbhsg_uep_to_pipe (struct usbhsg_uep*) ; 
 int /*<<< orphan*/  usbhsg_ureq_to_pkt (struct usbhsg_request*) ; 

__attribute__((used)) static int usbhsg_ep_dequeue(struct usb_ep *ep, struct usb_request *req)
{
	struct usbhsg_uep *uep = usbhsg_ep_to_uep(ep);
	struct usbhsg_request *ureq = usbhsg_req_to_ureq(req);
	struct usbhs_pipe *pipe;
	unsigned long flags;

	spin_lock_irqsave(&uep->lock, flags);
	pipe = usbhsg_uep_to_pipe(uep);
	if (pipe)
		usbhs_pkt_pop(pipe, usbhsg_ureq_to_pkt(ureq));

	/*
	 * To dequeue a request, this driver should call the usbhsg_queue_pop()
	 * even if the pipe is NULL.
	 */
	usbhsg_queue_pop(uep, ureq, -ECONNRESET);
	spin_unlock_irqrestore(&uep->lock, flags);

	return 0;
}