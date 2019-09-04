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
typedef  int u32 ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 int WIRELESS_MODE_AC_24G ; 
 int WIRELESS_MODE_AC_5G ; 
 int WIRELESS_MODE_N_24G ; 

__attribute__((used)) static u8 _rtl8822be_get_vht_en(enum wireless_mode wirelessmode,
				u32 ratr_bitmap)
{
	u8 ret = 0;

	if (wirelessmode < WIRELESS_MODE_N_24G) {
		ret = 0;
	} else if (wirelessmode == WIRELESS_MODE_AC_24G) {
		if (ratr_bitmap & 0xfff00000) /* Mix , 2SS */
			ret = 3;
		else /* Mix, 1SS */
			ret = 2;
	} else if (wirelessmode == WIRELESS_MODE_AC_5G) {
		ret = 1;
	} /* VHT */

	return ret << 4;
}