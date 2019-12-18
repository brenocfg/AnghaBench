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
struct ieee80211_channel {int flags; } ;

/* Variables and functions */
 unsigned long IEEE80211_CHANNEL_TIME ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 unsigned long IEEE80211_PASSIVE_CHANNEL_TIME ; 
 unsigned long IEEE80211_PROBE_DELAY ; 

__attribute__((used)) static unsigned long
ieee80211_scan_get_channel_time(struct ieee80211_channel *chan)
{
	/*
	 * TODO: channel switching also consumes quite some time,
	 * add that delay as well to get a better estimation
	 */
	if (chan->flags & (IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_RADAR))
		return IEEE80211_PASSIVE_CHANNEL_TIME;
	return IEEE80211_PROBE_DELAY + IEEE80211_CHANNEL_TIME;
}