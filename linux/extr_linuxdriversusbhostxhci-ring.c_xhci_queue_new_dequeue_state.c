#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xhci_virt_ep {int ep_state; int /*<<< orphan*/  queued_deq_ptr; TYPE_2__* queued_deq_seg; } ;
struct xhci_hcd {TYPE_1__** devs; } ;
struct xhci_dequeue_state {int new_cycle_state; scalar_t__ stream_id; int /*<<< orphan*/  new_deq_ptr; TYPE_2__* new_deq_seg; } ;
struct xhci_command {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {scalar_t__ dma; } ;
struct TYPE_4__ {struct xhci_virt_ep* eps; } ;

/* Variables and functions */
 int EP_ID_FOR_TRB (unsigned int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SCT_FOR_TRB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCT_PRI_TR ; 
 int SET_DEQ_PENDING ; 
 int SLOT_ID_FOR_TRB (unsigned int) ; 
 int STREAM_ID_FOR_TRB (scalar_t__) ; 
 int /*<<< orphan*/  TRB_SET_DEQ ; 
 int TRB_TYPE (int /*<<< orphan*/ ) ; 
 int lower_32_bits (scalar_t__) ; 
 int queue_command (struct xhci_hcd*,struct xhci_command*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  trace_xhci_dbg_cancel_urb ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,TYPE_2__*,unsigned long long,int /*<<< orphan*/ ,unsigned long long,int) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 scalar_t__ xhci_trb_virt_to_dma (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

void xhci_queue_new_dequeue_state(struct xhci_hcd *xhci,
		unsigned int slot_id, unsigned int ep_index,
		struct xhci_dequeue_state *deq_state)
{
	dma_addr_t addr;
	u32 trb_slot_id = SLOT_ID_FOR_TRB(slot_id);
	u32 trb_ep_index = EP_ID_FOR_TRB(ep_index);
	u32 trb_stream_id = STREAM_ID_FOR_TRB(deq_state->stream_id);
	u32 trb_sct = 0;
	u32 type = TRB_TYPE(TRB_SET_DEQ);
	struct xhci_virt_ep *ep;
	struct xhci_command *cmd;
	int ret;

	xhci_dbg_trace(xhci, trace_xhci_dbg_cancel_urb,
		"Set TR Deq Ptr cmd, new deq seg = %p (0x%llx dma), new deq ptr = %p (0x%llx dma), new cycle = %u",
		deq_state->new_deq_seg,
		(unsigned long long)deq_state->new_deq_seg->dma,
		deq_state->new_deq_ptr,
		(unsigned long long)xhci_trb_virt_to_dma(
			deq_state->new_deq_seg, deq_state->new_deq_ptr),
		deq_state->new_cycle_state);

	addr = xhci_trb_virt_to_dma(deq_state->new_deq_seg,
				    deq_state->new_deq_ptr);
	if (addr == 0) {
		xhci_warn(xhci, "WARN Cannot submit Set TR Deq Ptr\n");
		xhci_warn(xhci, "WARN deq seg = %p, deq pt = %p\n",
			  deq_state->new_deq_seg, deq_state->new_deq_ptr);
		return;
	}
	ep = &xhci->devs[slot_id]->eps[ep_index];
	if ((ep->ep_state & SET_DEQ_PENDING)) {
		xhci_warn(xhci, "WARN Cannot submit Set TR Deq Ptr\n");
		xhci_warn(xhci, "A Set TR Deq Ptr command is pending.\n");
		return;
	}

	/* This function gets called from contexts where it cannot sleep */
	cmd = xhci_alloc_command(xhci, false, GFP_ATOMIC);
	if (!cmd)
		return;

	ep->queued_deq_seg = deq_state->new_deq_seg;
	ep->queued_deq_ptr = deq_state->new_deq_ptr;
	if (deq_state->stream_id)
		trb_sct = SCT_FOR_TRB(SCT_PRI_TR);
	ret = queue_command(xhci, cmd,
		lower_32_bits(addr) | trb_sct | deq_state->new_cycle_state,
		upper_32_bits(addr), trb_stream_id,
		trb_slot_id | trb_ep_index | type, false);
	if (ret < 0) {
		xhci_free_command(xhci, cmd);
		return;
	}

	/* Stop the TD queueing code from ringing the doorbell until
	 * this command completes.  The HC won't set the dequeue pointer
	 * if the ring is running, and ringing the doorbell starts the
	 * ring running.
	 */
	ep->ep_state |= SET_DEQ_PENDING;
}