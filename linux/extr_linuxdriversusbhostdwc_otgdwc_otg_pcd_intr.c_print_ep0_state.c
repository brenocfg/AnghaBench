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
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;

/* Variables and functions */

__attribute__((used)) static inline void print_ep0_state(dwc_otg_pcd_t * pcd)
{
#ifdef DEBUG
	char str[40];

	switch (pcd->ep0state) {
	case EP0_DISCONNECT:
		dwc_strcpy(str, "EP0_DISCONNECT");
		break;
	case EP0_IDLE:
		dwc_strcpy(str, "EP0_IDLE");
		break;
	case EP0_IN_DATA_PHASE:
		dwc_strcpy(str, "EP0_IN_DATA_PHASE");
		break;
	case EP0_OUT_DATA_PHASE:
		dwc_strcpy(str, "EP0_OUT_DATA_PHASE");
		break;
	case EP0_IN_STATUS_PHASE:
		dwc_strcpy(str, "EP0_IN_STATUS_PHASE");
		break;
	case EP0_OUT_STATUS_PHASE:
		dwc_strcpy(str, "EP0_OUT_STATUS_PHASE");
		break;
	case EP0_STALL:
		dwc_strcpy(str, "EP0_STALL");
		break;
	default:
		dwc_strcpy(str, "EP0_INVALID");
	}

	DWC_DEBUGPL(DBG_ANY, "%s(%d)\n", str, pcd->ep0state);
#endif
}