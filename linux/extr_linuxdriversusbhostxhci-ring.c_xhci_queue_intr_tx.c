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
struct xhci_hcd {TYPE_1__** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  out_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_interval (struct xhci_hcd*,struct urb*,struct xhci_ep_ctx*) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 int xhci_queue_bulk_tx (struct xhci_hcd*,int /*<<< orphan*/ ,struct urb*,int,unsigned int) ; 

int xhci_queue_intr_tx(struct xhci_hcd *xhci, gfp_t mem_flags,
		struct urb *urb, int slot_id, unsigned int ep_index)
{
	struct xhci_ep_ctx *ep_ctx;

	ep_ctx = xhci_get_ep_ctx(xhci, xhci->devs[slot_id]->out_ctx, ep_index);
	check_interval(xhci, urb, ep_ctx);

	return xhci_queue_bulk_tx(xhci, mem_flags, urb, slot_id, ep_index);
}