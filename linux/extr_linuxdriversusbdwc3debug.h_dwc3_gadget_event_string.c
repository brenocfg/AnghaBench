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
struct dwc3_event_devt {int event_info; int type; } ;
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
#define  DWC3_DEVICE_EVENT_CMD_CMPL 137 
#define  DWC3_DEVICE_EVENT_CONNECT_DONE 136 
#define  DWC3_DEVICE_EVENT_DISCONNECT 135 
#define  DWC3_DEVICE_EVENT_EOPF 134 
#define  DWC3_DEVICE_EVENT_ERRATIC_ERROR 133 
#define  DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE 132 
#define  DWC3_DEVICE_EVENT_OVERFLOW 131 
#define  DWC3_DEVICE_EVENT_RESET 130 
#define  DWC3_DEVICE_EVENT_SOF 129 
#define  DWC3_DEVICE_EVENT_WAKEUP 128 
 int DWC3_LINK_STATE_MASK ; 
 char* dwc3_gadget_link_string (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static inline const char *
dwc3_gadget_event_string(char *str, const struct dwc3_event_devt *event)
{
	enum dwc3_link_state state = event->event_info & DWC3_LINK_STATE_MASK;

	switch (event->type) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		sprintf(str, "Disconnect: [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_RESET:
		sprintf(str, "Reset [%s]", dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		sprintf(str, "Connection Done [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		sprintf(str, "Link Change [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_WAKEUP:
		sprintf(str, "WakeUp [%s]", dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_EOPF:
		sprintf(str, "End-Of-Frame [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_SOF:
		sprintf(str, "Start-Of-Frame [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_ERRATIC_ERROR:
		sprintf(str, "Erratic Error [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_CMD_CMPL:
		sprintf(str, "Command Complete [%s]",
				dwc3_gadget_link_string(state));
		break;
	case DWC3_DEVICE_EVENT_OVERFLOW:
		sprintf(str, "Overflow [%s]", dwc3_gadget_link_string(state));
		break;
	default:
		sprintf(str, "UNKNOWN");
	}

	return str;
}