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
typedef  enum power_supply_type { ____Placeholder_power_supply_type } power_supply_type ;

/* Variables and functions */
#define  POWER_SUPPLY_TYPE_USB 130 
#define  POWER_SUPPLY_TYPE_USB_CDP 129 
#define  POWER_SUPPLY_TYPE_USB_DCP 128 

__attribute__((used)) static const char *chg_to_string(enum power_supply_type chg_type)
{
	switch (chg_type) {
	case POWER_SUPPLY_TYPE_USB:
		return "USB_SDP_CHARGER";
	case POWER_SUPPLY_TYPE_USB_DCP:
		return "USB_DCP_CHARGER";
	case POWER_SUPPLY_TYPE_USB_CDP:
		return "USB_CDP_CHARGER";
	default:
		return "INVALID_CHARGER";
	}
}