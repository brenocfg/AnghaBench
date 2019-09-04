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
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int dummy; } ;

/* Variables and functions */
 unsigned int COMP_BABBLE_DETECTED_ERROR ; 
 unsigned int COMP_SPLIT_TRANSACTION_ERROR ; 
 unsigned int COMP_USB_TRANSACTION_ERROR ; 
 scalar_t__ EP_STATE_HALTED ; 
 scalar_t__ GET_EP_CTX_STATE (struct xhci_ep_ctx*) ; 

__attribute__((used)) static int xhci_requires_manual_halt_cleanup(struct xhci_hcd *xhci,
		struct xhci_ep_ctx *ep_ctx,
		unsigned int trb_comp_code)
{
	/* TRB completion codes that may require a manual halt cleanup */
	if (trb_comp_code == COMP_USB_TRANSACTION_ERROR ||
			trb_comp_code == COMP_BABBLE_DETECTED_ERROR ||
			trb_comp_code == COMP_SPLIT_TRANSACTION_ERROR)
		/* The 0.95 spec says a babbling control endpoint
		 * is not halted. The 0.96 spec says it is.  Some HW
		 * claims to be 0.95 compliant, but it halts the control
		 * endpoint anyway.  Check if a babble halted the
		 * endpoint.
		 */
		if (GET_EP_CTX_STATE(ep_ctx) == EP_STATE_HALTED)
			return 1;

	return 0;
}