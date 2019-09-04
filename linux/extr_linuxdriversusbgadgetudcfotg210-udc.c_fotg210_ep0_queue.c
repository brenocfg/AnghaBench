#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ length; scalar_t__ actual; } ;
struct fotg210_request {TYPE_3__ req; } ;
struct TYPE_4__ {scalar_t__ maxpacket; } ;
struct fotg210_ep {TYPE_2__* fotg210; TYPE_1__ ep; scalar_t__ dir_in; } ;
struct TYPE_5__ {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMISGR0_MCX_OUT_INT ; 
 scalar_t__ FOTG210_DMISGR0 ; 
 int /*<<< orphan*/  fotg210_done (struct fotg210_ep*,struct fotg210_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fotg210_start_dma (struct fotg210_ep*,struct fotg210_request*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fotg210_ep0_queue(struct fotg210_ep *ep,
				struct fotg210_request *req)
{
	if (!req->req.length) {
		fotg210_done(ep, req, 0);
		return;
	}
	if (ep->dir_in) { /* if IN */
		fotg210_start_dma(ep, req);
		if ((req->req.length == req->req.actual) ||
		    (req->req.actual < ep->ep.maxpacket))
			fotg210_done(ep, req, 0);
	} else { /* OUT */
		u32 value = ioread32(ep->fotg210->reg + FOTG210_DMISGR0);

		value &= ~DMISGR0_MCX_OUT_INT;
		iowrite32(value, ep->fotg210->reg + FOTG210_DMISGR0);
	}
}