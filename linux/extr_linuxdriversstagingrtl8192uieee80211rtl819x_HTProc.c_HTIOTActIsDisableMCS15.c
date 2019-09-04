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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool HTIOTActIsDisableMCS15(struct ieee80211_device *ieee)
{
	bool retValue = false;

#ifdef TODO
	// Apply for 819u only
#if (HAL_CODE_BASE == RTL8192)

#if (DEV_BUS_TYPE == USB_INTERFACE)
	// Alway disable MCS15 by Jerry Chang's request.by Emily, 2008.04.15
	retValue = true;
#elif (DEV_BUS_TYPE == PCI_INTERFACE)
	// Enable MCS15 if the peer is Cisco AP. by Emily, 2008.05.12
//	if(pBssDesc->bCiscoCapExist)
//		retValue = false;
//	else
		retValue = false;
#endif
#endif
#endif
	// Jerry Chang suggest that 8190 1x2 does not need to disable MCS15

	return retValue;
}