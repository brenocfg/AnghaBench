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
struct xhci_virt_ep {int ep_state; TYPE_3__* ring; TYPE_2__* stream_info; } ;
struct xhci_hcd {TYPE_1__** devs; } ;
struct TYPE_6__ {scalar_t__ dequeue; } ;
struct TYPE_5__ {int num_streams; } ;
struct TYPE_4__ {struct xhci_virt_ep* eps; } ;

/* Variables and functions */
 int EP_HAS_STREAMS ; 
 int LAST_EP_INDEX ; 
 int /*<<< orphan*/  xhci_ring_ep_doorbell (struct xhci_hcd*,int,int,int) ; 

void xhci_ring_device(struct xhci_hcd *xhci, int slot_id)
{
	int i, s;
	struct xhci_virt_ep *ep;

	for (i = 0; i < LAST_EP_INDEX + 1; i++) {
		ep = &xhci->devs[slot_id]->eps[i];

		if (ep->ep_state & EP_HAS_STREAMS) {
			for (s = 1; s < ep->stream_info->num_streams; s++)
				xhci_ring_ep_doorbell(xhci, slot_id, i, s);
		} else if (ep->ring && ep->ring->dequeue) {
			xhci_ring_ep_doorbell(xhci, slot_id, i, 0);
		}
	}

	return;
}