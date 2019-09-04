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
struct TYPE_2__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
typedef  int u32 ;
struct xhci_segment {int dummy; } ;
struct xhci_ring {struct xhci_segment* deq_seg; union xhci_trb* dequeue; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int TRB_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_trb (struct xhci_hcd*,struct xhci_ring*,struct xhci_segment**,union xhci_trb**) ; 
 int /*<<< orphan*/  trb_is_link (union xhci_trb*) ; 
 int /*<<< orphan*/  trb_is_noop (union xhci_trb*) ; 

__attribute__((used)) static int sum_trb_lengths(struct xhci_hcd *xhci, struct xhci_ring *ring,
			   union xhci_trb *stop_trb)
{
	u32 sum;
	union xhci_trb *trb = ring->dequeue;
	struct xhci_segment *seg = ring->deq_seg;

	for (sum = 0; trb != stop_trb; next_trb(xhci, ring, &seg, &trb)) {
		if (!trb_is_noop(trb) && !trb_is_link(trb))
			sum += TRB_LEN(le32_to_cpu(trb->generic.field[2]));
	}
	return sum;
}