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
struct wiphy {int regulatory_flags; int /*<<< orphan*/ * bands; } ;
struct regulatory_request {int /*<<< orphan*/  dfs_region; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_2__ {int /*<<< orphan*/  dfs_region; } ;

/* Variables and functions */
 int NL80211_REGDOM_SET_BY_CORE ; 
 int NUM_NL80211_BANDS ; 
 int REGULATORY_CUSTOM_REG ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 TYPE_1__* get_cfg80211_regdom () ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  handle_band (struct wiphy*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ignore_reg_update (struct wiphy*,int) ; 
 int /*<<< orphan*/  reg_call_notifier (struct wiphy*,struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_process_beacons (struct wiphy*) ; 
 int /*<<< orphan*/  reg_process_ht_flags (struct wiphy*) ; 

__attribute__((used)) static void wiphy_update_regulatory(struct wiphy *wiphy,
				    enum nl80211_reg_initiator initiator)
{
	enum nl80211_band band;
	struct regulatory_request *lr = get_last_request();

	if (ignore_reg_update(wiphy, initiator)) {
		/*
		 * Regulatory updates set by CORE are ignored for custom
		 * regulatory cards. Let us notify the changes to the driver,
		 * as some drivers used this to restore its orig_* reg domain.
		 */
		if (initiator == NL80211_REGDOM_SET_BY_CORE &&
		    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG &&
		    !(wiphy->regulatory_flags &
		      REGULATORY_WIPHY_SELF_MANAGED))
			reg_call_notifier(wiphy, lr);
		return;
	}

	lr->dfs_region = get_cfg80211_regdom()->dfs_region;

	for (band = 0; band < NUM_NL80211_BANDS; band++)
		handle_band(wiphy, initiator, wiphy->bands[band]);

	reg_process_beacons(wiphy);
	reg_process_ht_flags(wiphy);
	reg_call_notifier(wiphy, lr);
}