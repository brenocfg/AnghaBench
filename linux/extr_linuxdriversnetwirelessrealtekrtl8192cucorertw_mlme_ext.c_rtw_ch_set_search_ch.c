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
typedef  int u32 ;
struct TYPE_3__ {int const ChannelNum; } ;
typedef  TYPE_1__ RT_CHANNEL_INFO ;

/* Variables and functions */

int rtw_ch_set_search_ch(RT_CHANNEL_INFO *ch_set, const u32 ch)
{
	int i;
	for(i=0;ch_set[i].ChannelNum!=0;i++){
		if(ch == ch_set[i].ChannelNum)
			break;
	}
	
	if(i >= ch_set[i].ChannelNum)
		return -1;
	return i;
}