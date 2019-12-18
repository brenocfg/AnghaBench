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
struct wiphy {int dummy; } ;
struct reg_beacon {int /*<<< orphan*/  list; int /*<<< orphan*/  chan; } ;
struct ieee80211_channel {int flags; scalar_t__ band; int /*<<< orphan*/  center_freq; scalar_t__ beacon_found; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  freq_is_chan_12_13_14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 struct reg_beacon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_channel*,int) ; 
 int pending_reg_beacon (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_pending_beacons ; 
 int /*<<< orphan*/  reg_pending_beacons_lock ; 
 int /*<<< orphan*/  reg_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_name (struct wiphy*) ; 

int regulatory_hint_found_beacon(struct wiphy *wiphy,
				 struct ieee80211_channel *beacon_chan,
				 gfp_t gfp)
{
	struct reg_beacon *reg_beacon;
	bool processing;

	if (beacon_chan->beacon_found ||
	    beacon_chan->flags & IEEE80211_CHAN_RADAR ||
	    (beacon_chan->band == NL80211_BAND_2GHZ &&
	     !freq_is_chan_12_13_14(beacon_chan->center_freq)))
		return 0;

	spin_lock_bh(&reg_pending_beacons_lock);
	processing = pending_reg_beacon(beacon_chan);
	spin_unlock_bh(&reg_pending_beacons_lock);

	if (processing)
		return 0;

	reg_beacon = kzalloc(sizeof(struct reg_beacon), gfp);
	if (!reg_beacon)
		return -ENOMEM;

	pr_debug("Found new beacon on frequency: %d MHz (Ch %d) on %s\n",
		 beacon_chan->center_freq,
		 ieee80211_frequency_to_channel(beacon_chan->center_freq),
		 wiphy_name(wiphy));

	memcpy(&reg_beacon->chan, beacon_chan,
	       sizeof(struct ieee80211_channel));

	/*
	 * Since we can be called from BH or and non-BH context
	 * we must use spin_lock_bh()
	 */
	spin_lock_bh(&reg_pending_beacons_lock);
	list_add_tail(&reg_beacon->list, &reg_pending_beacons);
	spin_unlock_bh(&reg_pending_beacons_lock);

	schedule_work(&reg_work);

	return 0;
}