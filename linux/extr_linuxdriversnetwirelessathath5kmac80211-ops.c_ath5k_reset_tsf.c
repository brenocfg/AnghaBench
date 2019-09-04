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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_hw {scalar_t__ opmode; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  ath5k_beacon_update_timers (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reset_tsf (struct ath5k_hw*) ; 

__attribute__((used)) static void
ath5k_reset_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct ath5k_hw *ah = hw->priv;

	/*
	 * in IBSS mode we need to update the beacon timers too.
	 * this will also reset the TSF if we call it with 0
	 */
	if (ah->opmode == NL80211_IFTYPE_ADHOC)
		ath5k_beacon_update_timers(ah, 0);
	else
		ath5k_hw_reset_tsf(ah);
}