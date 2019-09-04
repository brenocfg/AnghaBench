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
typedef  int /*<<< orphan*/  u32 ;
struct dwc2_hsotg_ep {int dir_in; scalar_t__ target_frame; int interval; int /*<<< orphan*/  index; int /*<<< orphan*/  isochronous; struct dwc2_hsotg* parent; } ;
struct dwc2_hsotg {scalar_t__ frame_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOEPCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOEPMSK ; 
 int /*<<< orphan*/  DOEPMSK_OUTTKNEPDISMSK ; 
 int /*<<< orphan*/  DXEPCTL_SETEVENFR ; 
 int /*<<< orphan*/  DXEPCTL_SETODDFR ; 
 scalar_t__ TARGET_FRAME_INITIAL ; 
 int /*<<< orphan*/  dwc2_gadget_incr_frame_num (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_gadget_start_isoc_ddma (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_gadget_start_next_request (struct dwc2_hsotg_ep*) ; 
 int /*<<< orphan*/  dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_writel (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ using_desc_dma (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_gadget_handle_out_token_ep_disabled(struct dwc2_hsotg_ep *ep)
{
	struct dwc2_hsotg *hsotg = ep->parent;
	int dir_in = ep->dir_in;
	u32 doepmsk;

	if (dir_in || !ep->isochronous)
		return;

	if (using_desc_dma(hsotg)) {
		if (ep->target_frame == TARGET_FRAME_INITIAL) {
			/* Start first ISO Out */
			ep->target_frame = hsotg->frame_number;
			dwc2_gadget_start_isoc_ddma(ep);
		}
		return;
	}

	if (ep->interval > 1 &&
	    ep->target_frame == TARGET_FRAME_INITIAL) {
		u32 ctrl;

		ep->target_frame = hsotg->frame_number;
		dwc2_gadget_incr_frame_num(ep);

		ctrl = dwc2_readl(hsotg, DOEPCTL(ep->index));
		if (ep->target_frame & 0x1)
			ctrl |= DXEPCTL_SETODDFR;
		else
			ctrl |= DXEPCTL_SETEVENFR;

		dwc2_writel(hsotg, ctrl, DOEPCTL(ep->index));
	}

	dwc2_gadget_start_next_request(ep);
	doepmsk = dwc2_readl(hsotg, DOEPMSK);
	doepmsk &= ~DOEPMSK_OUTTKNEPDISMSK;
	dwc2_writel(hsotg, doepmsk, DOEPMSK);
}