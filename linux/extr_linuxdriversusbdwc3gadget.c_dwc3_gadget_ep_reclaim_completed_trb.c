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
struct dwc3_trb {int ctrl; unsigned int size; } ;
struct dwc3_request {unsigned int remaining; scalar_t__ unaligned; scalar_t__ zero; } ;
struct dwc3_event_depevt {int status; } ;
struct dwc3_ep {int dummy; } ;

/* Variables and functions */
 int DEPEVT_STATUS_IOC ; 
 int DEPEVT_STATUS_SHORT ; 
 int DWC3_TRB_CTRL_CHN ; 
 int DWC3_TRB_CTRL_HWO ; 
 unsigned int DWC3_TRB_SIZE_MASK ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  dwc3_ep_inc_deq (struct dwc3_ep*) ; 
 int /*<<< orphan*/  trace_dwc3_complete_trb (struct dwc3_ep*,struct dwc3_trb*) ; 

__attribute__((used)) static int dwc3_gadget_ep_reclaim_completed_trb(struct dwc3_ep *dep,
		struct dwc3_request *req, struct dwc3_trb *trb,
		const struct dwc3_event_depevt *event, int status, int chain)
{
	unsigned int		count;

	dwc3_ep_inc_deq(dep);

	trace_dwc3_complete_trb(dep, trb);

	/*
	 * If we're in the middle of series of chained TRBs and we
	 * receive a short transfer along the way, DWC3 will skip
	 * through all TRBs including the last TRB in the chain (the
	 * where CHN bit is zero. DWC3 will also avoid clearing HWO
	 * bit and SW has to do it manually.
	 *
	 * We're going to do that here to avoid problems of HW trying
	 * to use bogus TRBs for transfers.
	 */
	if (chain && (trb->ctrl & DWC3_TRB_CTRL_HWO))
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;

	/*
	 * If we're dealing with unaligned size OUT transfer, we will be left
	 * with one TRB pending in the ring. We need to manually clear HWO bit
	 * from that TRB.
	 */
	if ((req->zero || req->unaligned) && !(trb->ctrl & DWC3_TRB_CTRL_CHN)) {
		trb->ctrl &= ~DWC3_TRB_CTRL_HWO;
		return 1;
	}

	count = trb->size & DWC3_TRB_SIZE_MASK;
	req->remaining += count;

	if ((trb->ctrl & DWC3_TRB_CTRL_HWO) && status != -ESHUTDOWN)
		return 1;

	if (event->status & DEPEVT_STATUS_SHORT && !chain)
		return 1;

	if (event->status & DEPEVT_STATUS_IOC)
		return 1;

	return 0;
}