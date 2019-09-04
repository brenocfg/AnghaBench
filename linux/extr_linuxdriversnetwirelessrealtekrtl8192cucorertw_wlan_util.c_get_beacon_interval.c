#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  IEs; } ;
typedef  TYPE_1__ WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16_to_cpu (unsigned short) ; 
 int /*<<< orphan*/  rtw_get_beacon_interval_from_ie (int /*<<< orphan*/ ) ; 

u16 get_beacon_interval(WLAN_BSSID_EX *bss)
{
	unsigned short val;
	_rtw_memcpy((unsigned char *)&val, rtw_get_beacon_interval_from_ie(bss->IEs), 2);

	return le16_to_cpu(val);	

}