#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct at91_udc {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int status; } ;
struct at91_request {TYPE_2__ req; int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct at91_ep {unsigned int stopped; int int_mask; int /*<<< orphan*/  queue; TYPE_1__ ep; struct at91_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_IDR ; 
 int EINPROGRESS ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  VDBG (char*,int /*<<< orphan*/ ,struct at91_request*,int) ; 
 int /*<<< orphan*/  at91_udp_write (struct at91_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_gadget_giveback_request (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static void done(struct at91_ep *ep, struct at91_request *req, int status)
{
	unsigned	stopped = ep->stopped;
	struct at91_udc	*udc = ep->udc;

	list_del_init(&req->queue);
	if (req->req.status == -EINPROGRESS)
		req->req.status = status;
	else
		status = req->req.status;
	if (status && status != -ESHUTDOWN)
		VDBG("%s done %p, status %d\n", ep->ep.name, req, status);

	ep->stopped = 1;
	spin_unlock(&udc->lock);
	usb_gadget_giveback_request(&ep->ep, &req->req);
	spin_lock(&udc->lock);
	ep->stopped = stopped;

	/* ep0 is always ready; other endpoints need a non-empty queue */
	if (list_empty(&ep->queue) && ep->int_mask != (1 << 0))
		at91_udp_write(udc, AT91_UDP_IDR, ep->int_mask);
}