#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xhci_virt_ep {int ep_state; TYPE_1__* ring; } ;
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; struct xhci_virt_ep* eps; } ;
struct xhci_input_control_ctx {int dummy; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; struct xhci_virt_device** devs; } ;
struct xhci_command {int /*<<< orphan*/  completion; TYPE_2__* in_ctx; } ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; scalar_t__ hcpriv; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {size_t slot_id; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  td_list; } ;

/* Variables and functions */
 scalar_t__ EP0_FLAG ; 
 int EP_HARD_CLEAR_TOGGLE ; 
 int EP_SOFT_CLEAR_TOGGLE ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ SLOT_FLAG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_endpoint_xfer_control (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 struct xhci_command* xhci_alloc_command_with_ctx (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_endpoint_copy (struct xhci_hcd*,TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 scalar_t__ xhci_get_endpoint_flag (int /*<<< orphan*/ *) ; 
 unsigned int xhci_get_endpoint_index (int /*<<< orphan*/ *) ; 
 struct xhci_input_control_ctx* xhci_get_input_control_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  xhci_queue_configure_endpoint (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  xhci_queue_stop_endpoint (struct xhci_hcd*,struct xhci_command*,size_t,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_setup_input_ctx_for_config_ep (struct xhci_hcd*,TYPE_2__*,int /*<<< orphan*/ ,struct xhci_input_control_ctx*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void xhci_endpoint_reset(struct usb_hcd *hcd,
		struct usb_host_endpoint *host_ep)
{
	struct xhci_hcd *xhci;
	struct usb_device *udev;
	struct xhci_virt_device *vdev;
	struct xhci_virt_ep *ep;
	struct xhci_input_control_ctx *ctrl_ctx;
	struct xhci_command *stop_cmd, *cfg_cmd;
	unsigned int ep_index;
	unsigned long flags;
	u32 ep_flag;

	xhci = hcd_to_xhci(hcd);
	if (!host_ep->hcpriv)
		return;
	udev = (struct usb_device *) host_ep->hcpriv;
	vdev = xhci->devs[udev->slot_id];
	ep_index = xhci_get_endpoint_index(&host_ep->desc);
	ep = &vdev->eps[ep_index];

	/* Bail out if toggle is already being cleared by a endpoint reset */
	if (ep->ep_state & EP_HARD_CLEAR_TOGGLE) {
		ep->ep_state &= ~EP_HARD_CLEAR_TOGGLE;
		return;
	}
	/* Only interrupt and bulk ep's use data toggle, USB2 spec 5.5.4-> */
	if (usb_endpoint_xfer_control(&host_ep->desc) ||
	    usb_endpoint_xfer_isoc(&host_ep->desc))
		return;

	ep_flag = xhci_get_endpoint_flag(&host_ep->desc);

	if (ep_flag == SLOT_FLAG || ep_flag == EP0_FLAG)
		return;

	stop_cmd = xhci_alloc_command(xhci, true, GFP_NOWAIT);
	if (!stop_cmd)
		return;

	cfg_cmd = xhci_alloc_command_with_ctx(xhci, true, GFP_NOWAIT);
	if (!cfg_cmd)
		goto cleanup;

	spin_lock_irqsave(&xhci->lock, flags);

	/* block queuing new trbs and ringing ep doorbell */
	ep->ep_state |= EP_SOFT_CLEAR_TOGGLE;

	/*
	 * Make sure endpoint ring is empty before resetting the toggle/seq.
	 * Driver is required to synchronously cancel all transfer request.
	 * Stop the endpoint to force xHC to update the output context
	 */

	if (!list_empty(&ep->ring->td_list)) {
		dev_err(&udev->dev, "EP not empty, refuse reset\n");
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_free_command(xhci, cfg_cmd);
		goto cleanup;
	}
	xhci_queue_stop_endpoint(xhci, stop_cmd, udev->slot_id, ep_index, 0);
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	wait_for_completion(stop_cmd->completion);

	spin_lock_irqsave(&xhci->lock, flags);

	/* config ep command clears toggle if add and drop ep flags are set */
	ctrl_ctx = xhci_get_input_control_ctx(cfg_cmd->in_ctx);
	xhci_setup_input_ctx_for_config_ep(xhci, cfg_cmd->in_ctx, vdev->out_ctx,
					   ctrl_ctx, ep_flag, ep_flag);
	xhci_endpoint_copy(xhci, cfg_cmd->in_ctx, vdev->out_ctx, ep_index);

	xhci_queue_configure_endpoint(xhci, cfg_cmd, cfg_cmd->in_ctx->dma,
				      udev->slot_id, false);
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	wait_for_completion(cfg_cmd->completion);

	ep->ep_state &= ~EP_SOFT_CLEAR_TOGGLE;
	xhci_free_command(xhci, cfg_cmd);
cleanup:
	xhci_free_command(xhci, stop_cmd);
}