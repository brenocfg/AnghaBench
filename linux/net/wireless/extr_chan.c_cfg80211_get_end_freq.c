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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 cfg80211_get_end_freq(u32 center_freq,
				 u32 bandwidth)
{
	u32 end_freq;

	if (bandwidth <= 20)
		end_freq = center_freq;
	else
		end_freq = center_freq + bandwidth/2 - 10;

	return end_freq;
}