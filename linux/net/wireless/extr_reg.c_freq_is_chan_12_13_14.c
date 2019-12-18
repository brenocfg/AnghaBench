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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 scalar_t__ ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool freq_is_chan_12_13_14(u32 freq)
{
	if (freq == ieee80211_channel_to_frequency(12, NL80211_BAND_2GHZ) ||
	    freq == ieee80211_channel_to_frequency(13, NL80211_BAND_2GHZ) ||
	    freq == ieee80211_channel_to_frequency(14, NL80211_BAND_2GHZ))
		return true;
	return false;
}