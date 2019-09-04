#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mv_udc {int /*<<< orphan*/  gadget; TYPE_4__* dev; scalar_t__ test_mode; struct mv_req* status_req; int /*<<< orphan*/  ep0_state; int /*<<< orphan*/  ep0_dir; struct mv_ep* eps; } ;
struct TYPE_10__ {int length; scalar_t__ dma; scalar_t__ buf; int /*<<< orphan*/ * complete; scalar_t__ actual; int /*<<< orphan*/  status; } ;
struct mv_req {int mapped; TYPE_5__ req; int /*<<< orphan*/  queue; scalar_t__ dtd_count; scalar_t__ test_mode; struct mv_ep* ep; } ;
struct mv_ep {int /*<<< orphan*/  queue; TYPE_3__* udc; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;
struct TYPE_8__ {TYPE_2__ gadget; } ;

/* Variables and functions */
 scalar_t__ DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WAIT_FOR_OUT_STATUS ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ep_dir (struct mv_ep*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * prime_status_complete ; 
 int queue_dtd (struct mv_ep*,struct mv_req*) ; 
 int /*<<< orphan*/  req_to_dtd (struct mv_req*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static int
udc_prime_status(struct mv_udc *udc, u8 direction, u16 status, bool empty)
{
	int retval = 0;
	struct mv_req *req;
	struct mv_ep *ep;

	ep = &udc->eps[0];
	udc->ep0_dir = direction;
	udc->ep0_state = WAIT_FOR_OUT_STATUS;

	req = udc->status_req;

	/* fill in the reqest structure */
	if (empty == false) {
		*((u16 *) req->req.buf) = cpu_to_le16(status);
		req->req.length = 2;
	} else
		req->req.length = 0;

	req->ep = ep;
	req->req.status = -EINPROGRESS;
	req->req.actual = 0;
	if (udc->test_mode) {
		req->req.complete = prime_status_complete;
		req->test_mode = udc->test_mode;
		udc->test_mode = 0;
	} else
		req->req.complete = NULL;
	req->dtd_count = 0;

	if (req->req.dma == DMA_ADDR_INVALID) {
		req->req.dma = dma_map_single(ep->udc->gadget.dev.parent,
				req->req.buf, req->req.length,
				ep_dir(ep) ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		req->mapped = 1;
	}

	/* prime the data phase */
	if (!req_to_dtd(req)) {
		retval = queue_dtd(ep, req);
		if (retval) {
			dev_err(&udc->dev->dev,
				"Failed to queue dtd when prime status\n");
			goto out;
		}
	} else{	/* no mem */
		retval = -ENOMEM;
		dev_err(&udc->dev->dev,
			"Failed to dma_pool_alloc when prime status\n");
		goto out;
	}

	list_add_tail(&req->queue, &ep->queue);

	return 0;
out:
	usb_gadget_unmap_request(&udc->gadget, &req->req, ep_dir(ep));

	return retval;
}