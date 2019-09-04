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
struct TYPE_9__ {int status; scalar_t__ dma; } ;
struct ast_vhub_req {int internal; TYPE_4__ req; int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_in; } ;
struct ast_vhub_ep {TYPE_3__* vhub; int /*<<< orphan*/  ep; TYPE_2__ epn; TYPE_1__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*,struct ast_vhub_req*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  usb_gadget_unmap_request (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

void ast_vhub_done(struct ast_vhub_ep *ep, struct ast_vhub_req *req,
		   int status)
{
	bool internal = req->internal;

	EPVDBG(ep, "completing request @%p, status %d\n", req, status);

	list_del_init(&req->queue);

	if (req->req.status == -EINPROGRESS)
		req->req.status = status;

	if (req->req.dma) {
		if (!WARN_ON(!ep->dev))
			usb_gadget_unmap_request(&ep->dev->gadget,
						 &req->req, ep->epn.is_in);
		req->req.dma = 0;
	}

	/*
	 * If this isn't an internal EP0 request, call the core
	 * to call the gadget completion.
	 */
	if (!internal) {
		spin_unlock(&ep->vhub->lock);
		usb_gadget_giveback_request(&ep->ep, &req->req);
		spin_lock(&ep->vhub->lock);
	}
}