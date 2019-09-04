#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ frequency; scalar_t__ channel; } ;

/* Variables and functions */
 TYPE_1__* ch_freq_map ; 
 size_t ch_freq_map_num ; 

u32 rtw_freq2ch(u32 freq)
{
	u8	i;
	u32	ch = 0;

	for (i = 0; i < ch_freq_map_num; i++)
	{
		if (freq == ch_freq_map[i].frequency)
		{
			ch = ch_freq_map[i].channel;
				break;
		}
	}
	if (i == ch_freq_map_num)
		ch = 1;

	return ch;
}