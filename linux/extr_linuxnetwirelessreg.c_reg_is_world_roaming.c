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
struct ieee80211_regdomain {int /*<<< orphan*/  alpha2; } ;

/* Variables and functions */
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int REGULATORY_CUSTOM_REG ; 
 struct ieee80211_regdomain* get_cfg80211_regdom () ; 
 struct regulatory_request* get_last_request () ; 
 struct ieee80211_regdomain* get_wiphy_regdom (struct wiphy*) ; 
 scalar_t__ is_world_regdom (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool reg_is_world_roaming(struct wiphy *wiphy)
{
	const struct ieee80211_regdomain *cr = get_cfg80211_regdom();
	const struct ieee80211_regdomain *wr = get_wiphy_regdom(wiphy);
	struct regulatory_request *lr = get_last_request();

	if (is_world_regdom(cr->alpha2) || (wr && is_world_regdom(wr->alpha2)))
		return true;

	if (lr && lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    wiphy->regulatory_flags & REGULATORY_CUSTOM_REG)
		return true;

	return false;
}