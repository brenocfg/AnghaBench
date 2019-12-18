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
struct wiphy {int regulatory_flags; } ;
struct regulatory_request {scalar_t__ initiator; } ;

/* Variables and functions */
 scalar_t__ NL80211_REGDOM_SET_BY_USER ; 
 int REGULATORY_COUNTRY_IE_IGNORE ; 
 int REGULATORY_DISABLE_BEACON_HINTS ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 struct regulatory_request* get_last_request () ; 
 int /*<<< orphan*/  reg_call_notifier (struct wiphy*,struct regulatory_request*) ; 
 int /*<<< orphan*/  reg_dev_ignore_cell_hint (struct wiphy*) ; 
 int /*<<< orphan*/  reg_num_devs_support_basehint ; 
 int /*<<< orphan*/  wiphy_all_share_dfs_chan_state (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_update_regulatory (struct wiphy*,scalar_t__) ; 

void wiphy_regulatory_register(struct wiphy *wiphy)
{
	struct regulatory_request *lr = get_last_request();

	/* self-managed devices ignore beacon hints and country IE */
	if (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED) {
		wiphy->regulatory_flags |= REGULATORY_DISABLE_BEACON_HINTS |
					   REGULATORY_COUNTRY_IE_IGNORE;

		/*
		 * The last request may have been received before this
		 * registration call. Call the driver notifier if
		 * initiator is USER.
		 */
		if (lr->initiator == NL80211_REGDOM_SET_BY_USER)
			reg_call_notifier(wiphy, lr);
	}

	if (!reg_dev_ignore_cell_hint(wiphy))
		reg_num_devs_support_basehint++;

	wiphy_update_regulatory(wiphy, lr->initiator);
	wiphy_all_share_dfs_chan_state(wiphy);
}