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
typedef  enum dwc3_link_state { ____Placeholder_dwc3_link_state } dwc3_link_state ;

/* Variables and functions */
#define  DWC3_LINK_STATE_CMPLY 141 
#define  DWC3_LINK_STATE_HRESET 140 
#define  DWC3_LINK_STATE_LPBK 139 
#define  DWC3_LINK_STATE_POLL 138 
#define  DWC3_LINK_STATE_RECOV 137 
#define  DWC3_LINK_STATE_RESET 136 
#define  DWC3_LINK_STATE_RESUME 135 
#define  DWC3_LINK_STATE_RX_DET 134 
#define  DWC3_LINK_STATE_SS_DIS 133 
#define  DWC3_LINK_STATE_SS_INACT 132 
#define  DWC3_LINK_STATE_U0 131 
#define  DWC3_LINK_STATE_U1 130 
#define  DWC3_LINK_STATE_U2 129 
#define  DWC3_LINK_STATE_U3 128 

__attribute__((used)) static inline const char *
dwc3_gadget_link_string(enum dwc3_link_state link_state)
{
	switch (link_state) {
	case DWC3_LINK_STATE_U0:
		return "U0";
	case DWC3_LINK_STATE_U1:
		return "U1";
	case DWC3_LINK_STATE_U2:
		return "U2";
	case DWC3_LINK_STATE_U3:
		return "U3";
	case DWC3_LINK_STATE_SS_DIS:
		return "SS.Disabled";
	case DWC3_LINK_STATE_RX_DET:
		return "RX.Detect";
	case DWC3_LINK_STATE_SS_INACT:
		return "SS.Inactive";
	case DWC3_LINK_STATE_POLL:
		return "Polling";
	case DWC3_LINK_STATE_RECOV:
		return "Recovery";
	case DWC3_LINK_STATE_HRESET:
		return "Hot Reset";
	case DWC3_LINK_STATE_CMPLY:
		return "Compliance";
	case DWC3_LINK_STATE_LPBK:
		return "Loopback";
	case DWC3_LINK_STATE_RESET:
		return "Reset";
	case DWC3_LINK_STATE_RESUME:
		return "Resume";
	default:
		return "UNKNOWN link state\n";
	}
}