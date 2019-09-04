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
struct xhci_td {TYPE_1__* urb; } ;
struct xhci_hcd {int quirks; } ;
struct xhci_dequeue_state {int /*<<< orphan*/  new_deq_seg; int /*<<< orphan*/  new_deq_ptr; } ;
struct usb_device {int /*<<< orphan*/  slot_id; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int XHCI_RESET_EP_QUIRK ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 int /*<<< orphan*/  trace_xhci_dbg_reset_ep ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xhci_find_new_dequeue_state (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct xhci_td*,struct xhci_dequeue_state*) ; 
 int /*<<< orphan*/  xhci_queue_new_dequeue_state (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int,struct xhci_dequeue_state*) ; 
 int /*<<< orphan*/  xhci_setup_input_ctx_for_quirk (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int,struct xhci_dequeue_state*) ; 

void xhci_cleanup_stalled_ring(struct xhci_hcd *xhci, unsigned int ep_index,
			       unsigned int stream_id, struct xhci_td *td)
{
	struct xhci_dequeue_state deq_state;
	struct usb_device *udev = td->urb->dev;

	xhci_dbg_trace(xhci, trace_xhci_dbg_reset_ep,
			"Cleaning up stalled endpoint ring");
	/* We need to move the HW's dequeue pointer past this TD,
	 * or it will attempt to resend it on the next doorbell ring.
	 */
	xhci_find_new_dequeue_state(xhci, udev->slot_id,
			ep_index, stream_id, td, &deq_state);

	if (!deq_state.new_deq_ptr || !deq_state.new_deq_seg)
		return;

	/* HW with the reset endpoint quirk will use the saved dequeue state to
	 * issue a configure endpoint command later.
	 */
	if (!(xhci->quirks & XHCI_RESET_EP_QUIRK)) {
		xhci_dbg_trace(xhci, trace_xhci_dbg_reset_ep,
				"Queueing new dequeue state");
		xhci_queue_new_dequeue_state(xhci, udev->slot_id,
				ep_index, &deq_state);
	} else {
		/* Better hope no one uses the input context between now and the
		 * reset endpoint completion!
		 * XXX: No idea how this hardware will react when stream rings
		 * are enabled.
		 */
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Setting up input context for "
				"configure endpoint command");
		xhci_setup_input_ctx_for_quirk(xhci, udev->slot_id,
				ep_index, &deq_state);
	}
}