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
typedef  int u8 ;

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

__attribute__((used)) static inline const char *dwc3_gadget_event_type_string(u8 event)
{
	switch (event) {
	case DWC3_DEVICE_EVENT_DISCONNECT:
		return "Disconnect";
	case DWC3_DEVICE_EVENT_RESET:
		return "Reset";
	case DWC3_DEVICE_EVENT_CONNECT_DONE:
		return "Connect Done";
	case DWC3_DEVICE_EVENT_LINK_STATUS_CHANGE:
		return "Link Status Change";
	case DWC3_DEVICE_EVENT_WAKEUP:
		return "Wake-Up";
	case DWC3_DEVICE_EVENT_HIBER_REQ:
		return "Hibernation";
	case DWC3_DEVICE_EVENT_EOPF:
		return "End of Periodic Frame";
	case DWC3_DEVICE_EVENT_SOF:
		return "Start of Frame";
	case DWC3_DEVICE_EVENT_ERRATIC_ERROR:
		return "Erratic Error";
	case DWC3_DEVICE_EVENT_CMD_CMPL:
		return "Command Complete";
	case DWC3_DEVICE_EVENT_OVERFLOW:
		return "Overflow";
	default:
		return "UNKNOWN";
	}
}