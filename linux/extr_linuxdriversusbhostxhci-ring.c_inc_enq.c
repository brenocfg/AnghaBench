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
struct TYPE_5__ {int /*<<< orphan*/  control; } ;
struct TYPE_4__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_2__ link; TYPE_1__ generic; } ;
typedef  int u32 ;
struct xhci_ring {scalar_t__ type; int cycle_state; union xhci_trb* enqueue; TYPE_3__* enq_seg; int /*<<< orphan*/  num_trbs_free; } ;
struct xhci_hcd {int quirks; } ;
struct TYPE_6__ {union xhci_trb* trbs; struct TYPE_6__* next; } ;

/* Variables and functions */
 int TRB_CHAIN ; 
 int TRB_CYCLE ; 
 scalar_t__ TYPE_ISOC ; 
 int XHCI_AMD_0x96_HOST ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ link_trb_toggles_cycle (union xhci_trb*) ; 
 int /*<<< orphan*/  trace_xhci_inc_enq (struct xhci_ring*) ; 
 scalar_t__ trb_is_link (union xhci_trb*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  xhci_link_trb_quirk (struct xhci_hcd*) ; 

__attribute__((used)) static void inc_enq(struct xhci_hcd *xhci, struct xhci_ring *ring,
			bool more_trbs_coming)
{
	u32 chain;
	union xhci_trb *next;

	chain = le32_to_cpu(ring->enqueue->generic.field[3]) & TRB_CHAIN;
	/* If this is not event ring, there is one less usable TRB */
	if (!trb_is_link(ring->enqueue))
		ring->num_trbs_free--;
	next = ++(ring->enqueue);

	/* Update the dequeue pointer further if that was a link TRB */
	while (trb_is_link(next)) {

		/*
		 * If the caller doesn't plan on enqueueing more TDs before
		 * ringing the doorbell, then we don't want to give the link TRB
		 * to the hardware just yet. We'll give the link TRB back in
		 * prepare_ring() just before we enqueue the TD at the top of
		 * the ring.
		 */
		if (!chain && !more_trbs_coming)
			break;

		/* If we're not dealing with 0.95 hardware or isoc rings on
		 * AMD 0.96 host, carry over the chain bit of the previous TRB
		 * (which may mean the chain bit is cleared).
		 */
		if (!(ring->type == TYPE_ISOC &&
		      (xhci->quirks & XHCI_AMD_0x96_HOST)) &&
		    !xhci_link_trb_quirk(xhci)) {
			next->link.control &= cpu_to_le32(~TRB_CHAIN);
			next->link.control |= cpu_to_le32(chain);
		}
		/* Give this link TRB to the hardware */
		wmb();
		next->link.control ^= cpu_to_le32(TRB_CYCLE);

		/* Toggle the cycle bit after the last ring segment. */
		if (link_trb_toggles_cycle(next))
			ring->cycle_state ^= 1;

		ring->enq_seg = ring->enq_seg->next;
		ring->enqueue = ring->enq_seg->trbs;
		next = ring->enqueue;
	}

	trace_xhci_inc_enq(ring);
}