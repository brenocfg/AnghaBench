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

/* Variables and functions */
 scalar_t__ CHANNEL_WIDTH_40 ; 
 scalar_t__ CHANNEL_WIDTH_80 ; 
 scalar_t__ HAL_PRIME_CHNL_OFFSET_LOWER ; 

u8 rtw_get_center_ch(u8 channel, u8 chnl_bw, u8 chnl_offset)
{
	u8 center_ch = channel;

	if (chnl_bw == CHANNEL_WIDTH_80) {
		if ((channel == 36) || (channel == 40) || (channel == 44) || (channel == 48))
			center_ch = 42;
		if ((channel == 52) || (channel == 56) || (channel == 60) || (channel == 64))
			center_ch = 58;
		if ((channel == 100) || (channel == 104) || (channel == 108) || (channel == 112))
			center_ch = 106;
		if ((channel == 116) || (channel == 120) || (channel == 124) || (channel == 128))
			center_ch = 122;
		if ((channel == 132) || (channel == 136) || (channel == 140) || (channel == 144))
			center_ch = 138;
		if ((channel == 149) || (channel == 153) || (channel == 157) || (channel == 161))
			center_ch = 155;
		else if (channel <= 14)
			center_ch = 7;
	} else if (chnl_bw == CHANNEL_WIDTH_40) {
		if (chnl_offset == HAL_PRIME_CHNL_OFFSET_LOWER)
			center_ch = channel + 2;
		else
			center_ch = channel - 2;
	}

	return center_ch;
}