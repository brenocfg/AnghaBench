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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;

/* Variables and functions */
 size_t FCS_LEN ; 
 scalar_t__ IE_HDR_LEN ; 
 size_t TAG_PARAM_OFFSET ; 
 scalar_t__ WLAN_EID_DS_PARAMS ; 

__attribute__((used)) static u8 get_current_channel_802_11n(u8 *msa, u16 rx_len)
{
	u16 index;

	index = TAG_PARAM_OFFSET;
	while (index < (rx_len - FCS_LEN)) {
		if (msa[index] == WLAN_EID_DS_PARAMS)
			return msa[index + 2];
		index += msa[index + 1] + IE_HDR_LEN;
	}

	return 0;
}