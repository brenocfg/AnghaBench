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
typedef  int u32 ;
struct ieee80211_channel {scalar_t__ center_freq; } ;
struct cfg80211_chan_def {int center_freq1; int center_freq2; TYPE_1__* chan; } ;
struct TYPE_2__ {scalar_t__ center_freq; } ;

/* Variables and functions */
 int cfg80211_chandef_get_width (struct cfg80211_chan_def*) ; 

bool cfg80211_is_sub_chan(struct cfg80211_chan_def *chandef,
			  struct ieee80211_channel *chan)
{
	int width;
	u32 freq;

	if (chandef->chan->center_freq == chan->center_freq)
		return true;

	width = cfg80211_chandef_get_width(chandef);
	if (width <= 20)
		return false;

	for (freq = chandef->center_freq1 - width / 2 + 10;
	     freq <= chandef->center_freq1 + width / 2 - 10; freq += 20) {
		if (chan->center_freq == freq)
			return true;
	}

	if (!chandef->center_freq2)
		return false;

	for (freq = chandef->center_freq2 - width / 2 + 10;
	     freq <= chandef->center_freq2 + width / 2 - 10; freq += 20) {
		if (chan->center_freq == freq)
			return true;
	}

	return false;
}