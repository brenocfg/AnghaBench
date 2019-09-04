#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct omap_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; } ;
struct TYPE_5__ {int status; int /*<<< orphan*/  length; int /*<<< orphan*/  actual; } ;
struct omap_req {TYPE_1__ req; int /*<<< orphan*/  queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct omap_ep {unsigned int stopped; int bEndpointAddress; struct omap_udc* udc; TYPE_2__ ep; scalar_t__ has_dma; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ESHUTDOWN ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  VDBG (char*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static void
done(struct omap_ep *ep, struct omap_req *req, int status)
{
	struct omap_udc		*udc = ep->udc;
	unsigned		stopped = ep->stopped;

	list_del_init(&req->queue);

	if (req->req.status == -EINPROGRESS)
		req->req.status = status;
	else
		status = req->req.status;

	if (use_dma && ep->has_dma)
		usb_gadget_unmap_request(&udc->gadget, &req->req,
				(ep->bEndpointAddress & USB_DIR_IN));

#ifndef	USB_TRACE
	if (status && status != -ESHUTDOWN)
#endif
		VDBG("complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* don't modify queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&ep->udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&ep->udc->lock);
	ep->stopped = stopped;
}