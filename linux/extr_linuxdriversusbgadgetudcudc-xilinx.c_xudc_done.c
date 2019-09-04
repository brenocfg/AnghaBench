#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xusb_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; scalar_t__ dma_enabled; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  (* complete ) (TYPE_2__*,TYPE_1__*) ;scalar_t__ length; } ;
struct xusb_req {TYPE_1__ usb_req; int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct xusb_ep {TYPE_2__ ep_usb; int /*<<< orphan*/  is_in; scalar_t__ epnumber; struct xusb_udc* udc; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct xusb_req*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xudc_done(struct xusb_ep *ep, struct xusb_req *req, int status)
{
	struct xusb_udc *udc = ep->udc;

	list_del_init(&req->queue);

	if (req->usb_req.status == -EINPROGRESS)
		req->usb_req.status = status;
	else
		status = req->usb_req.status;

	if (status && status != -ESHUTDOWN)
		dev_dbg(udc->dev, "%s done %p, status %d\n",
			ep->ep_usb.name, req, status);
	/* unmap request if DMA is present*/
	if (udc->dma_enabled && ep->epnumber && req->usb_req.length)
		usb_gadget_unmap_request(&udc->gadget, &req->usb_req,
					 ep->is_in);

	if (req->usb_req.complete) {
		spin_unlock(&udc->lock);
		req->usb_req.complete(&ep->ep_usb, &req->usb_req);
		spin_lock(&udc->lock);
	}
}