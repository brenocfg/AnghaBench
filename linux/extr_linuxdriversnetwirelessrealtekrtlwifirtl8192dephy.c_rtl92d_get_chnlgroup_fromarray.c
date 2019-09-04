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

u8 rtl92d_get_chnlgroup_fromarray(u8 chnl)
{
	u8 group;
	u8 channel_info[59] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56,
		58, 60, 62, 64, 100, 102, 104, 106, 108,
		110, 112, 114, 116, 118, 120, 122, 124,
		126, 128, 130, 132, 134, 136, 138, 140,
		149, 151, 153, 155, 157, 159, 161, 163,
		165
	};

	if (channel_info[chnl] <= 3)
		group = 0;
	else if (channel_info[chnl] <= 9)
		group = 1;
	else if (channel_info[chnl] <= 14)
		group = 2;
	else if (channel_info[chnl] <= 44)
		group = 3;
	else if (channel_info[chnl] <= 54)
		group = 4;
	else if (channel_info[chnl] <= 64)
		group = 5;
	else if (channel_info[chnl] <= 112)
		group = 6;
	else if (channel_info[chnl] <= 126)
		group = 7;
	else if (channel_info[chnl] <= 140)
		group = 8;
	else if (channel_info[chnl] <= 153)
		group = 9;
	else if (channel_info[chnl] <= 159)
		group = 10;
	else
		group = 11;
	return group;
}