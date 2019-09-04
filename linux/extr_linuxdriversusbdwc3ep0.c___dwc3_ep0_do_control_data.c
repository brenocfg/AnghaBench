#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int length; int /*<<< orphan*/  dma; scalar_t__ zero; } ;
struct dwc3_request {int direction; int /*<<< orphan*/ * trb; TYPE_2__ request; } ;
struct TYPE_3__ {int maxpacket; } ;
struct dwc3_ep {scalar_t__ number; int trb_enqueue; TYPE_1__ endpoint; } ;
struct dwc3 {int ep0_bounced; int /*<<< orphan*/ * ep0_trb; int /*<<< orphan*/  sysdev; int /*<<< orphan*/  bounce_addr; int /*<<< orphan*/  ep0_trb_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_TRBCTL_CONTROL_DATA ; 
 scalar_t__ IS_ALIGNED (int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dwc3_ep0_prepare_one_trb (struct dwc3_ep*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int dwc3_ep0_start_trans (struct dwc3_ep*) ; 
 int usb_gadget_map_request_by_dev (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void __dwc3_ep0_do_control_data(struct dwc3 *dwc,
		struct dwc3_ep *dep, struct dwc3_request *req)
{
	int			ret;

	req->direction = !!dep->number;

	if (req->request.length == 0) {
		dwc3_ep0_prepare_one_trb(dep, dwc->ep0_trb_addr, 0,
				DWC3_TRBCTL_CONTROL_DATA, false);
		ret = dwc3_ep0_start_trans(dep);
	} else if (!IS_ALIGNED(req->request.length, dep->endpoint.maxpacket)
			&& (dep->number == 0)) {
		u32	maxpacket;
		u32	rem;

		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		if (ret)
			return;

		maxpacket = dep->endpoint.maxpacket;
		rem = req->request.length % maxpacket;
		dwc->ep0_bounced = true;

		/* prepare normal TRB */
		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
					 req->request.length,
					 DWC3_TRBCTL_CONTROL_DATA,
					 true);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue - 1];

		/* Now prepare one extra TRB to align transfer size */
		dwc3_ep0_prepare_one_trb(dep, dwc->bounce_addr,
					 maxpacket - rem,
					 DWC3_TRBCTL_CONTROL_DATA,
					 false);
		ret = dwc3_ep0_start_trans(dep);
	} else if (IS_ALIGNED(req->request.length, dep->endpoint.maxpacket) &&
		   req->request.length && req->request.zero) {

		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		if (ret)
			return;

		/* prepare normal TRB */
		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
					 req->request.length,
					 DWC3_TRBCTL_CONTROL_DATA,
					 true);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue - 1];

		/* Now prepare one extra TRB to align transfer size */
		dwc3_ep0_prepare_one_trb(dep, dwc->bounce_addr,
					 0, DWC3_TRBCTL_CONTROL_DATA,
					 false);
		ret = dwc3_ep0_start_trans(dep);
	} else {
		ret = usb_gadget_map_request_by_dev(dwc->sysdev,
				&req->request, dep->number);
		if (ret)
			return;

		dwc3_ep0_prepare_one_trb(dep, req->request.dma,
				req->request.length, DWC3_TRBCTL_CONTROL_DATA,
				false);

		req->trb = &dwc->ep0_trb[dep->trb_enqueue];

		ret = dwc3_ep0_start_trans(dep);
	}

	WARN_ON(ret < 0);
}