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

__attribute__((used)) static u8 _rtl92d_phy_get_chnlgroup_bypg(u8 chnlindex)
{
	u8 group;
	u8 channel_info[59] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58,
		60, 62, 64, 100, 102, 104, 106, 108, 110, 112,
		114, 116, 118, 120, 122, 124, 126, 128,	130, 132,
		134, 136, 138, 140, 149, 151, 153, 155, 157, 159,
		161, 163, 165
	};

	if (channel_info[chnlindex] <= 3)	/* Chanel 1-3 */
		group = 0;
	else if (channel_info[chnlindex] <= 9)	/* Channel 4-9 */
		group = 1;
	else if (channel_info[chnlindex] <= 14)	/* Channel 10-14 */
		group = 2;
	else if (channel_info[chnlindex] <= 64)
		group = 6;
	else if (channel_info[chnlindex] <= 140)
		group = 7;
	else
		group = 8;
	return group;
}