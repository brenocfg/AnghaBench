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
typedef  int u32 ;
struct usb_gadget {int dummy; } ;
struct dwc3_ep {int flags; int /*<<< orphan*/  wait_end_transfer; } ;
struct dwc3 {int /*<<< orphan*/  ev_buf; int /*<<< orphan*/  irq_gadget; int /*<<< orphan*/  lock; int /*<<< orphan*/ * gadget_driver; int /*<<< orphan*/  dev; struct dwc3_ep** eps; } ;

/* Variables and functions */
 int DWC3_ENDPOINTS_NUM ; 
 int DWC3_EP_END_TRANSFER_PENDING ; 
 int /*<<< orphan*/  __dwc3_gadget_stop (struct dwc3*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dwc3* gadget_to_dwc (struct usb_gadget*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_event_interruptible_lock_irq_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_gadget_stop(struct usb_gadget *g)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;
	int			epnum;
	u32			tmo_eps = 0;

	spin_lock_irqsave(&dwc->lock, flags);

	if (pm_runtime_suspended(dwc->dev))
		goto out;

	__dwc3_gadget_stop(dwc);

	for (epnum = 2; epnum < DWC3_ENDPOINTS_NUM; epnum++) {
		struct dwc3_ep  *dep = dwc->eps[epnum];
		int ret;

		if (!dep)
			continue;

		if (!(dep->flags & DWC3_EP_END_TRANSFER_PENDING))
			continue;

		ret = wait_event_interruptible_lock_irq_timeout(dep->wait_end_transfer,
			    !(dep->flags & DWC3_EP_END_TRANSFER_PENDING),
			    dwc->lock, msecs_to_jiffies(5));

		if (ret <= 0) {
			/* Timed out or interrupted! There's nothing much
			 * we can do so we just log here and print which
			 * endpoints timed out at the end.
			 */
			tmo_eps |= 1 << epnum;
			dep->flags &= DWC3_EP_END_TRANSFER_PENDING;
		}
	}

	if (tmo_eps) {
		dev_err(dwc->dev,
			"end transfer timed out on endpoints 0x%x [bitmap]\n",
			tmo_eps);
	}

out:
	dwc->gadget_driver	= NULL;
	spin_unlock_irqrestore(&dwc->lock, flags);

	free_irq(dwc->irq_gadget, dwc->ev_buf);

	return 0;
}