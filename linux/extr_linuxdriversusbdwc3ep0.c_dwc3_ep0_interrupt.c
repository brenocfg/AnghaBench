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
struct dwc3_event_depevt {int endpoint_event; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
#define  DWC3_DEPEVT_EPCMDCMPLT 133 
#define  DWC3_DEPEVT_RXTXFIFOEVT 132 
#define  DWC3_DEPEVT_STREAMEVT 131 
#define  DWC3_DEPEVT_XFERCOMPLETE 130 
#define  DWC3_DEPEVT_XFERINPROGRESS 129 
#define  DWC3_DEPEVT_XFERNOTREADY 128 
 int /*<<< orphan*/  dwc3_ep0_xfer_complete (struct dwc3*,struct dwc3_event_depevt const*) ; 
 int /*<<< orphan*/  dwc3_ep0_xfernotready (struct dwc3*,struct dwc3_event_depevt const*) ; 

void dwc3_ep0_interrupt(struct dwc3 *dwc,
		const struct dwc3_event_depevt *event)
{
	switch (event->endpoint_event) {
	case DWC3_DEPEVT_XFERCOMPLETE:
		dwc3_ep0_xfer_complete(dwc, event);
		break;

	case DWC3_DEPEVT_XFERNOTREADY:
		dwc3_ep0_xfernotready(dwc, event);
		break;

	case DWC3_DEPEVT_XFERINPROGRESS:
	case DWC3_DEPEVT_RXTXFIFOEVT:
	case DWC3_DEPEVT_STREAMEVT:
	case DWC3_DEPEVT_EPCMDCMPLT:
		break;
	}
}