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
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_HT40 ; 

__attribute__((used)) static bool is_ht40_allowed(struct ieee80211_channel *chan)
{
	if (!chan)
		return false;
	if (chan->flags & IEEE80211_CHAN_DISABLED)
		return false;
	/* This would happen when regulatory rules disallow HT40 completely */
	if ((chan->flags & IEEE80211_CHAN_NO_HT40) == IEEE80211_CHAN_NO_HT40)
		return false;
	return true;
}