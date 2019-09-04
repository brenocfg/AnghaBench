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
typedef  int uint ;

/* Variables and functions */
 int WL_CHAN_FREQ_RANGE_2G ; 
 int WL_CHAN_FREQ_RANGE_5GH ; 
 int WL_CHAN_FREQ_RANGE_5GL ; 
 int WL_CHAN_FREQ_RANGE_5GM ; 

int wlc_phy_chanspec_freq2bandrange_lpssn(uint freq)
{
	int range = -1;

	if (freq < 2500)
		range = WL_CHAN_FREQ_RANGE_2G;
	else if (freq <= 5320)
		range = WL_CHAN_FREQ_RANGE_5GL;
	else if (freq <= 5700)
		range = WL_CHAN_FREQ_RANGE_5GM;
	else
		range = WL_CHAN_FREQ_RANGE_5GH;

	return range;
}