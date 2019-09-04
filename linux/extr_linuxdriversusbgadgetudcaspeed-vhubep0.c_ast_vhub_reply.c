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
struct usb_request {char* buf; int length; int zero; int /*<<< orphan*/ * complete; int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_3__* ops; } ;
struct TYPE_6__ {struct usb_request req; } ;
struct TYPE_7__ {int /*<<< orphan*/  dir_in; TYPE_1__ req; } ;
struct ast_vhub_ep {scalar_t__ d_idx; TYPE_4__* vhub; TYPE_5__ ep; TYPE_2__ ep0; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {scalar_t__ (* queue ) (TYPE_5__*,struct usb_request*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AST_VHUB_EP0_MAX_PACKET ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int std_req_data ; 
 int std_req_stall ; 
 scalar_t__ stub1 (TYPE_5__*,struct usb_request*,int /*<<< orphan*/ ) ; 

int ast_vhub_reply(struct ast_vhub_ep *ep, char *ptr, int len)
{
	struct usb_request *req = &ep->ep0.req.req;
	int rc;

	if (WARN_ON(ep->d_idx != 0))
		return std_req_stall;
	if (WARN_ON(!ep->ep0.dir_in))
		return std_req_stall;
	if (WARN_ON(len > AST_VHUB_EP0_MAX_PACKET))
		return std_req_stall;
	if (WARN_ON(req->status == -EINPROGRESS))
		return std_req_stall;

	req->buf = ptr;
	req->length = len;
	req->complete = NULL;
	req->zero = true;

	/*
	 * Call internal queue directly after dropping the lock. This is
	 * safe to do as the reply is always the last thing done when
	 * processing a SETUP packet, usually as a tail call
	 */
	spin_unlock(&ep->vhub->lock);
	if (ep->ep.ops->queue(&ep->ep, req, GFP_ATOMIC))
		rc = std_req_stall;
	else
		rc = std_req_data;
	spin_lock(&ep->vhub->lock);
	return rc;
}