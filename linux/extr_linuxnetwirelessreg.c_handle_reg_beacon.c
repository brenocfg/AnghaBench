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
struct wiphy {int regulatory_flags; struct ieee80211_supported_band** bands; } ;
struct TYPE_2__ {size_t band; scalar_t__ center_freq; } ;
struct reg_beacon {TYPE_1__ chan; } ;
struct ieee80211_supported_band {struct ieee80211_channel* channels; } ;
struct ieee80211_channel {scalar_t__ center_freq; int beacon_found; int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 int REGULATORY_DISABLE_BEACON_HINTS ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  nl80211_send_beacon_hint_event (struct wiphy*,struct ieee80211_channel*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  reg_is_world_roaming (struct wiphy*) ; 

__attribute__((used)) static void handle_reg_beacon(struct wiphy *wiphy, unsigned int chan_idx,
			      struct reg_beacon *reg_beacon)
{
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *chan;
	bool channel_changed = false;
	struct ieee80211_channel chan_before;

	sband = wiphy->bands[reg_beacon->chan.band];
	chan = &sband->channels[chan_idx];

	if (likely(chan->center_freq != reg_beacon->chan.center_freq))
		return;

	if (chan->beacon_found)
		return;

	chan->beacon_found = true;

	if (!reg_is_world_roaming(wiphy))
		return;

	if (wiphy->regulatory_flags & REGULATORY_DISABLE_BEACON_HINTS)
		return;

	chan_before = *chan;

	if (chan->flags & IEEE80211_CHAN_NO_IR) {
		chan->flags &= ~IEEE80211_CHAN_NO_IR;
		channel_changed = true;
	}

	if (channel_changed)
		nl80211_send_beacon_hint_event(wiphy, &chan_before, chan);
}