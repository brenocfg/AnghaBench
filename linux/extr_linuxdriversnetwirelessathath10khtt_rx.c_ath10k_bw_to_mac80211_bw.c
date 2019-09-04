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
 int RATE_INFO_BW_160 ; 
 int RATE_INFO_BW_20 ; 
 int RATE_INFO_BW_40 ; 
 int RATE_INFO_BW_80 ; 

__attribute__((used)) static inline u8 ath10k_bw_to_mac80211_bw(u8 bw)
{
	u8 ret = 0;

	switch (bw) {
	case 0:
		ret = RATE_INFO_BW_20;
		break;
	case 1:
		ret = RATE_INFO_BW_40;
		break;
	case 2:
		ret = RATE_INFO_BW_80;
		break;
	case 3:
		ret = RATE_INFO_BW_160;
		break;
	}

	return ret;
}