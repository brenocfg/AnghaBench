#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;
struct qe_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_2__ gadget; } ;
struct TYPE_9__ {int status; int /*<<< orphan*/  length; int /*<<< orphan*/  actual; int /*<<< orphan*/  dma; } ;
struct qe_req {TYPE_4__ req; scalar_t__ mapped; int /*<<< orphan*/  queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct qe_ep {unsigned char stopped; TYPE_3__ ep; struct qe_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINPROGRESS ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ep_is_in (struct qe_ep*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static void done(struct qe_ep *ep, struct qe_req *req, int status)
{
	struct qe_udc *udc = ep->udc;
	unsigned char stopped = ep->stopped;

	/* the req->queue pointer is used by ep_queue() func, in which
	 * the request will be added into a udc_ep->queue 'd tail
	 * so here the req will be dropped from the ep->queue
	 */
	list_del_init(&req->queue);

	/* req.status should be set as -EINPROGRESS in ep_queue() */
	if (req->req.status == -EINPROGRESS)
		req->req.status = status;
	else
		status = req->req.status;

	if (req->mapped) {
		dma_unmap_single(udc->gadget.dev.parent,
			req->req.dma, req->req.length,
			ep_is_in(ep)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);
		req->req.dma = DMA_ADDR_INVALID;
		req->mapped = 0;
	} else
		dma_sync_single_for_cpu(udc->gadget.dev.parent,
			req->req.dma, req->req.length,
			ep_is_in(ep)
				? DMA_TO_DEVICE
				: DMA_FROM_DEVICE);

	if (status && (status != -ESHUTDOWN))
		dev_vdbg(udc->dev, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);

	/* don't modify queue heads during completion callback */
	ep->stopped = 1;
	spin_unlock(&udc->lock);

	usb_gadget_giveback_request(&ep->ep, &req->req);

	spin_lock(&udc->lock);

	ep->stopped = stopped;
}