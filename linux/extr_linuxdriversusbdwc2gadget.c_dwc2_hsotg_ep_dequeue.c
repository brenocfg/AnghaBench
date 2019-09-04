#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_request {int dummy; } ;
struct usb_ep {int dummy; } ;
struct dwc2_hsotg_req {int dummy; } ;
struct dwc2_hsotg_ep {TYPE_1__* req; struct dwc2_hsotg* parent; } ;
struct dwc2_hsotg {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct usb_request req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct usb_ep*,struct usb_request*) ; 
 int /*<<< orphan*/  dwc2_hsotg_complete_request (struct dwc2_hsotg*,struct dwc2_hsotg_ep*,struct dwc2_hsotg_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_hsotg_ep_stop_xfr (struct dwc2_hsotg*,struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  on_list (struct dwc2_hsotg_ep*,struct dwc2_hsotg_req*) ; 
 struct dwc2_hsotg_ep* our_ep (struct usb_ep*) ; 
 struct dwc2_hsotg_req* our_req (struct usb_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc2_hsotg_ep_dequeue(struct usb_ep *ep, struct usb_request *req)
{
	struct dwc2_hsotg_req *hs_req = our_req(req);
	struct dwc2_hsotg_ep *hs_ep = our_ep(ep);
	struct dwc2_hsotg *hs = hs_ep->parent;
	unsigned long flags;

	dev_dbg(hs->dev, "ep_dequeue(%p,%p)\n", ep, req);

	spin_lock_irqsave(&hs->lock, flags);

	if (!on_list(hs_ep, hs_req)) {
		spin_unlock_irqrestore(&hs->lock, flags);
		return -EINVAL;
	}

	/* Dequeue already started request */
	if (req == &hs_ep->req->req)
		dwc2_hsotg_ep_stop_xfr(hs, hs_ep);

	dwc2_hsotg_complete_request(hs, hs_ep, hs_req, -ECONNRESET);
	spin_unlock_irqrestore(&hs->lock, flags);

	return 0;
}