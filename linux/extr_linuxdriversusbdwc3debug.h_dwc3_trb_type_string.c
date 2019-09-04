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

/* Variables and functions */
#define  DWC3_TRBCTL_CONTROL_DATA 135 
#define  DWC3_TRBCTL_CONTROL_SETUP 134 
#define  DWC3_TRBCTL_CONTROL_STATUS2 133 
#define  DWC3_TRBCTL_CONTROL_STATUS3 132 
#define  DWC3_TRBCTL_ISOCHRONOUS 131 
#define  DWC3_TRBCTL_ISOCHRONOUS_FIRST 130 
#define  DWC3_TRBCTL_LINK_TRB 129 
#define  DWC3_TRBCTL_NORMAL 128 

__attribute__((used)) static inline const char *dwc3_trb_type_string(unsigned int type)
{
	switch (type) {
	case DWC3_TRBCTL_NORMAL:
		return "normal";
	case DWC3_TRBCTL_CONTROL_SETUP:
		return "setup";
	case DWC3_TRBCTL_CONTROL_STATUS2:
		return "status2";
	case DWC3_TRBCTL_CONTROL_STATUS3:
		return "status3";
	case DWC3_TRBCTL_CONTROL_DATA:
		return "data";
	case DWC3_TRBCTL_ISOCHRONOUS_FIRST:
		return "isoc-first";
	case DWC3_TRBCTL_ISOCHRONOUS:
		return "isoc";
	case DWC3_TRBCTL_LINK_TRB:
		return "link";
	default:
		return "UNKNOWN";
	}
}