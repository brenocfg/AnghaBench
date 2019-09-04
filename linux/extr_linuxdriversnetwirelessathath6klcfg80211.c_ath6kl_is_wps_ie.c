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
 int const WLAN_EID_VENDOR_SPECIFIC ; 

__attribute__((used)) static bool ath6kl_is_wps_ie(const u8 *pos)
{
	return (pos[0] == WLAN_EID_VENDOR_SPECIFIC &&
		pos[1] >= 4 &&
		pos[2] == 0x00 && pos[3] == 0x50 && pos[4] == 0xf2 &&
		pos[5] == 0x04);
}