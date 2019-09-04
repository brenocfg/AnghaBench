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
struct dwc3_event_depevt {size_t endpoint_number; } ;
struct dwc3_ep {scalar_t__ resource_index; int /*<<< orphan*/  flags; } ;
struct dwc3 {int setup_packet_pending; int ep0state; struct dwc3_ep** eps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_EP_TRANSFER_STARTED ; 
#define  EP0_DATA_PHASE 130 
#define  EP0_SETUP_PHASE 129 
#define  EP0_STATUS_PHASE 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dwc3_ep0_complete_data (struct dwc3*,struct dwc3_event_depevt const*) ; 
 int /*<<< orphan*/  dwc3_ep0_complete_status (struct dwc3*,struct dwc3_event_depevt const*) ; 
 int /*<<< orphan*/  dwc3_ep0_inspect_setup (struct dwc3*,struct dwc3_event_depevt const*) ; 

__attribute__((used)) static void dwc3_ep0_xfer_complete(struct dwc3 *dwc,
			const struct dwc3_event_depevt *event)
{
	struct dwc3_ep		*dep = dwc->eps[event->endpoint_number];

	dep->flags &= ~DWC3_EP_TRANSFER_STARTED;
	dep->resource_index = 0;
	dwc->setup_packet_pending = false;

	switch (dwc->ep0state) {
	case EP0_SETUP_PHASE:
		dwc3_ep0_inspect_setup(dwc, event);
		break;

	case EP0_DATA_PHASE:
		dwc3_ep0_complete_data(dwc, event);
		break;

	case EP0_STATUS_PHASE:
		dwc3_ep0_complete_status(dwc, event);
		break;
	default:
		WARN(true, "UNKNOWN ep0state %d\n", dwc->ep0state);
	}
}