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
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  dma; scalar_t__ zero; scalar_t__ actual; } ;
struct usba_request {int submitted; scalar_t__ last_transaction; int /*<<< orphan*/  ctrl; TYPE_2__ req; scalar_t__ using_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct usba_ep {TYPE_1__ ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRESS ; 
 int /*<<< orphan*/  CONTROL ; 
 int /*<<< orphan*/  CTL_DIS ; 
 int /*<<< orphan*/  CTL_ENB ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct usba_request*,scalar_t__) ; 
 int /*<<< orphan*/  DBG_QUEUE ; 
 int /*<<< orphan*/  USBA_SHORT_PACKET ; 
 int /*<<< orphan*/  USBA_TX_COMPLETE ; 
 int /*<<< orphan*/  USBA_TX_PK_RDY ; 
 int /*<<< orphan*/  next_fifo_transaction (struct usba_ep*,struct usba_request*) ; 
 int /*<<< orphan*/  usba_dma_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void submit_request(struct usba_ep *ep, struct usba_request *req)
{
	DBG(DBG_QUEUE, "%s: submit_request: req %p (length %d)\n",
		ep->ep.name, req, req->req.length);

	req->req.actual = 0;
	req->submitted = 1;

	if (req->using_dma) {
		if (req->req.length == 0) {
			usba_ep_writel(ep, CTL_ENB, USBA_TX_PK_RDY);
			return;
		}

		if (req->req.zero)
			usba_ep_writel(ep, CTL_ENB, USBA_SHORT_PACKET);
		else
			usba_ep_writel(ep, CTL_DIS, USBA_SHORT_PACKET);

		usba_dma_writel(ep, ADDRESS, req->req.dma);
		usba_dma_writel(ep, CONTROL, req->ctrl);
	} else {
		next_fifo_transaction(ep, req);
		if (req->last_transaction) {
			usba_ep_writel(ep, CTL_DIS, USBA_TX_PK_RDY);
			usba_ep_writel(ep, CTL_ENB, USBA_TX_COMPLETE);
		} else {
			usba_ep_writel(ep, CTL_DIS, USBA_TX_COMPLETE);
			usba_ep_writel(ep, CTL_ENB, USBA_TX_PK_RDY);
		}
	}
}