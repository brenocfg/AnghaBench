#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_ep {int dummy; } ;
struct dwc3_ep {int number; int /*<<< orphan*/  flags; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_EP_WEDGE ; 
 int __dwc3_gadget_ep0_set_halt (struct usb_ep*,int) ; 
 int __dwc3_gadget_ep_set_halt (struct dwc3_ep*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dwc3_ep* to_dwc3_ep (struct usb_ep*) ; 

__attribute__((used)) static int dwc3_gadget_ep_set_wedge(struct usb_ep *ep)
{
	struct dwc3_ep			*dep = to_dwc3_ep(ep);
	struct dwc3			*dwc = dep->dwc;
	unsigned long			flags;
	int				ret;

	spin_lock_irqsave(&dwc->lock, flags);
	dep->flags |= DWC3_EP_WEDGE;

	if (dep->number == 0 || dep->number == 1)
		ret = __dwc3_gadget_ep0_set_halt(ep, 1);
	else
		ret = __dwc3_gadget_ep_set_halt(dep, 1, false);
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}