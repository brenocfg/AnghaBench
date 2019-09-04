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
typedef  enum dwc3_ep0_state { ____Placeholder_dwc3_ep0_state } dwc3_ep0_state ;

/* Variables and functions */
#define  EP0_DATA_PHASE 131 
#define  EP0_SETUP_PHASE 130 
#define  EP0_STATUS_PHASE 129 
#define  EP0_UNCONNECTED 128 

__attribute__((used)) static inline const char *dwc3_ep0_state_string(enum dwc3_ep0_state state)
{
	switch (state) {
	case EP0_UNCONNECTED:
		return "Unconnected";
	case EP0_SETUP_PHASE:
		return "Setup Phase";
	case EP0_DATA_PHASE:
		return "Data Phase";
	case EP0_STATUS_PHASE:
		return "Status Phase";
	default:
		return "UNKNOWN";
	}
}