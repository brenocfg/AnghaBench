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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_ring {TYPE_1__* enqueue; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_generic_trb {void** field; } ;
struct TYPE_2__ {struct xhci_generic_trb generic; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_enq (struct xhci_hcd*,struct xhci_ring*,int) ; 
 int /*<<< orphan*/  trace_xhci_queue_trb (struct xhci_ring*,struct xhci_generic_trb*) ; 

__attribute__((used)) static void queue_trb(struct xhci_hcd *xhci, struct xhci_ring *ring,
		bool more_trbs_coming,
		u32 field1, u32 field2, u32 field3, u32 field4)
{
	struct xhci_generic_trb *trb;

	trb = &ring->enqueue->generic;
	trb->field[0] = cpu_to_le32(field1);
	trb->field[1] = cpu_to_le32(field2);
	trb->field[2] = cpu_to_le32(field3);
	trb->field[3] = cpu_to_le32(field4);

	trace_xhci_queue_trb(ring, trb);

	inc_enq(xhci, ring, more_trbs_coming);
}