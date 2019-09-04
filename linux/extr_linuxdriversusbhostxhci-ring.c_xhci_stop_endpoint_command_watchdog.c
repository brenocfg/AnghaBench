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
struct xhci_virt_ep {int ep_state; int /*<<< orphan*/  stop_cmd_timer; struct xhci_hcd* xhci; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int EP_STOP_CMD_PENDING ; 
 struct xhci_virt_ep* ep ; 
 struct xhci_virt_ep* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stop_cmd_timer ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xhci_dbg_cancel_urb ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_halt (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_hc_died (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

void xhci_stop_endpoint_command_watchdog(struct timer_list *t)
{
	struct xhci_virt_ep *ep = from_timer(ep, t, stop_cmd_timer);
	struct xhci_hcd *xhci = ep->xhci;
	unsigned long flags;

	spin_lock_irqsave(&xhci->lock, flags);

	/* bail out if cmd completed but raced with stop ep watchdog timer.*/
	if (!(ep->ep_state & EP_STOP_CMD_PENDING) ||
	    timer_pending(&ep->stop_cmd_timer)) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg(xhci, "Stop EP timer raced with cmd completion, exit");
		return;
	}

	xhci_warn(xhci, "xHCI host not responding to stop endpoint command.\n");
	ep->ep_state &= ~EP_STOP_CMD_PENDING;

	xhci_halt(xhci);

	/*
	 * handle a stop endpoint cmd timeout as if host died (-ENODEV).
	 * In the future we could distinguish between -ENODEV and -ETIMEDOUT
	 * and try to recover a -ETIMEDOUT with a host controller reset
	 */
	xhci_hc_died(xhci);

	spin_unlock_irqrestore(&xhci->lock, flags);
	xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
			"xHCI host controller is dead.");
}