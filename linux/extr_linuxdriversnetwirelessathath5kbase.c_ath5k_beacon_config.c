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
struct ath5k_hw {int imask; scalar_t__ opmode; int /*<<< orphan*/  block; int /*<<< orphan*/  bhalq; scalar_t__ enable_beacon; scalar_t__ bmisscount; } ;

/* Variables and functions */
 int AR5K_INT_BMISS ; 
 int AR5K_INT_SWBA ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  ath5k_beacon_send (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_beacon_update_timers (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_beaconq_config (struct ath5k_hw*) ; 
 scalar_t__ ath5k_hw_hasveol (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_imr (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_stop_beacon_queue (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void
ath5k_beacon_config(struct ath5k_hw *ah)
{
	spin_lock_bh(&ah->block);
	ah->bmisscount = 0;
	ah->imask &= ~(AR5K_INT_BMISS | AR5K_INT_SWBA);

	if (ah->enable_beacon) {
		/*
		 * In IBSS mode we use a self-linked tx descriptor and let the
		 * hardware send the beacons automatically. We have to load it
		 * only once here.
		 * We use the SWBA interrupt only to keep track of the beacon
		 * timers in order to detect automatic TSF updates.
		 */
		ath5k_beaconq_config(ah);

		ah->imask |= AR5K_INT_SWBA;

		if (ah->opmode == NL80211_IFTYPE_ADHOC) {
			if (ath5k_hw_hasveol(ah))
				ath5k_beacon_send(ah);
		} else
			ath5k_beacon_update_timers(ah, -1);
	} else {
		ath5k_hw_stop_beacon_queue(ah, ah->bhalq);
	}

	ath5k_hw_set_imr(ah, ah->imask);
	mmiowb();
	spin_unlock_bh(&ah->block);
}