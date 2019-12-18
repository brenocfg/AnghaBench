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
#define  WSC_SECURITY_PRODUCT_STATE_EXPIRED 131 
#define  WSC_SECURITY_PRODUCT_STATE_OFF 130 
#define  WSC_SECURITY_PRODUCT_STATE_ON 129 
#define  WSC_SECURITY_PRODUCT_STATE_SNOOZED 128 

__attribute__((used)) static const char *get_str_for_state(int state)
{
	switch (state) {
	case WSC_SECURITY_PRODUCT_STATE_ON:
		return "enabled";
	case WSC_SECURITY_PRODUCT_STATE_OFF:
		return "disabled";
	case WSC_SECURITY_PRODUCT_STATE_SNOOZED:
		return "temporarily disabled";
	case WSC_SECURITY_PRODUCT_STATE_EXPIRED:
		return "expired";
	default:
		return "unknown";
	}
}