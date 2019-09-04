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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 

u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo)
{
	*buf++ = WLAN_EID_VENDOR_SPECIFIC;
	*buf++ = 7; /* len */
	*buf++ = 0x00; /* Microsoft OUI 00:50:F2 */
	*buf++ = 0x50;
	*buf++ = 0xf2;
	*buf++ = 2; /* WME */
	*buf++ = 0; /* WME info */
	*buf++ = 1; /* WME ver */
	*buf++ = qosinfo; /* U-APSD no in use */

	return buf;
}