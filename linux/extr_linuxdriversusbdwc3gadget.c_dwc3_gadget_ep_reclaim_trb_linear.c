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
struct dwc3_trb {int dummy; } ;
struct dwc3_request {int dummy; } ;
struct dwc3_event_depevt {int dummy; } ;
struct dwc3_ep {size_t trb_dequeue; struct dwc3_trb* trb_pool; } ;

/* Variables and functions */
 int dwc3_gadget_ep_reclaim_completed_trb (struct dwc3_ep*,struct dwc3_request*,struct dwc3_trb*,struct dwc3_event_depevt const*,int,int) ; 

__attribute__((used)) static int dwc3_gadget_ep_reclaim_trb_linear(struct dwc3_ep *dep,
		struct dwc3_request *req, const struct dwc3_event_depevt *event,
		int status)
{
	struct dwc3_trb *trb = &dep->trb_pool[dep->trb_dequeue];

	return dwc3_gadget_ep_reclaim_completed_trb(dep, req, trb,
			event, status, false);
}