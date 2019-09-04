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
struct dwc3_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {int /*<<< orphan*/  pending_list; int /*<<< orphan*/  name; TYPE_1__ endpoint; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EBUSY ; 
 int ESHUTDOWN ; 
 int __dwc3_gadget_ep0_queue (struct dwc3_ep*,struct dwc3_request*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dwc3_ep* to_dwc3_ep (struct usb_ep*) ; 
 struct dwc3_request* to_dwc3_request (struct usb_request*) ; 

int dwc3_gadget_ep0_queue(struct usb_ep *ep, struct usb_request *request,
		gfp_t gfp_flags)
{
	struct dwc3_request		*req = to_dwc3_request(request);
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;

	unsigned long			flags;

	int				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	if (!dep->endpoint.desc) {
		dev_err(dwc->dev, "%s: can't queue to disabled endpoint\n",
				dep->name);
		ret = -ESHUTDOWN;
		goto out;
	}

	/* we share one TRB for ep0/1 */
	if (!list_empty(&dep->pending_list)) {
		ret = -EBUSY;
		goto out;
	}

	ret = __dwc3_gadget_ep0_queue(dep, req);

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}