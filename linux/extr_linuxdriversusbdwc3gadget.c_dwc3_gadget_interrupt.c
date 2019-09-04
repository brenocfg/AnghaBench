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
struct dwc3_event_devt {int type; int /*<<< orphan*/  event_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct dwc3 {int /*<<< orphan*/  dev; TYPE_1__ gadget; int /*<<< orphan*/  revision; int /*<<< orphan*/  has_hibernation; } ;

/* Variables and functions */
#define  DWC3_DEVICE_EVENT_CMD_CMPL 138 
#define  DWC3_DEVICE_EVENT_CONNECT_DONE 137 
#define  DWC3_DEVICE_EVENT_DISCONNECT 136 
#define  DWC3_DEVICE_EVENT_EOPF 135 
#define  DWC3_DEVICE_EVENT_ERRATIC_ERROR 134 
#define  DWC3_DEVICE_EVENT_HIBER_REQ 133 
#define  DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE 132 
#define  DWC3_DEVICE_EVENT_OVERFLOW 131 
#define  DWC3_DEVICE_EVENT_RESET 130 
#define  DWC3_DEVICE_EVENT_SOF 129 
#define  DWC3_DEVICE_EVENT_WAKEUP 128 
 int /*<<< orphan*/  DWC3_REVISION_230A ; 
 int /*<<< orphan*/  USB_STATE_CONFIGURED ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dwc3_gadget_conndone_interrupt (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_disconnect_interrupt (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_hibernation_interrupt (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_gadget_linksts_change_interrupt (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_gadget_reset_interrupt (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_suspend_interrupt (struct dwc3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_gadget_wakeup_interrupt (struct dwc3*) ; 

__attribute__((used)) static void dwc3_gadget_interrupt(struct dwc3 *dwc,
		const struct dwc3_event_devt *event)
{
	switch (event->type) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		dwc3_gadget_disconnect_interrupt(dwc);
		break;
	case DWC3_DEVICE_EVENT_RESET:
		dwc3_gadget_reset_interrupt(dwc);
		break;
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		dwc3_gadget_conndone_interrupt(dwc);
		break;
	case DWC3_DEVICE_EVENT_WAKEUP:
		dwc3_gadget_wakeup_interrupt(dwc);
		break;
	case DWC3_DEVICE_EVENT_HIBER_REQ:
		if (dev_WARN_ONCE(dwc->dev, !dwc->has_hibernation,
					"unexpected hibernation event\n"))
			break;

		dwc3_gadget_hibernation_interrupt(dwc, event->event_info);
		break;
	case DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		dwc3_gadget_linksts_change_interrupt(dwc, event->event_info);
		break;
	case DWC3_DEVICE_EVENT_EOPF:
		/* It changed to be suspend event for version 2.30a and above */
		if (dwc->revision >= DWC3_REVISION_230A) {
			/*
			 * Ignore suspend event until the gadget enters into
			 * USB_STATE_CONFIGURED state.
			 */
			if (dwc->gadget.state >= USB_STATE_CONFIGURED)
				dwc3_gadget_suspend_interrupt(dwc,
						event->event_info);
		}
		break;
	case DWC3_DEVICE_EVENT_SOF:
	case DWC3_DEVICE_EVENT_ERRATIC_ERROR:
	case DWC3_DEVICE_EVENT_CMD_CMPL:
	case DWC3_DEVICE_EVENT_OVERFLOW:
		break;
	default:
		dev_WARN(dwc->dev, "UNKNOWN IRQ %d\n", event->type);
	}
}