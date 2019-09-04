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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  RATR_INX_WIRELESS_B 134 
#define  RATR_INX_WIRELESS_G 133 
#define  RATR_INX_WIRELESS_GB 132 
#define  RATR_INX_WIRELESS_N 131 
#define  RATR_INX_WIRELESS_NB 130 
#define  RATR_INX_WIRELESS_NG 129 
#define  RATR_INX_WIRELESS_NGB 128 

__attribute__((used)) static u8 _rtl8723be_mrate_idx_to_arfr_id(struct ieee80211_hw *hw,
					  u8 rate_index)
{
	u8 ret = 0;
	switch (rate_index) {
	case RATR_INX_WIRELESS_NGB:
		ret = 1;
		break;
	case RATR_INX_WIRELESS_N:
	case RATR_INX_WIRELESS_NG:
		ret = 5;
		break;
	case RATR_INX_WIRELESS_NB:
		ret = 3;
		break;
	case RATR_INX_WIRELESS_GB:
		ret = 6;
		break;
	case RATR_INX_WIRELESS_G:
		ret = 7;
		break;
	case RATR_INX_WIRELESS_B:
		ret = 8;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}