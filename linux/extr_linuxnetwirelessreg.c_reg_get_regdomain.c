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
struct wiphy {scalar_t__ regd; } ;
struct regulatory_request {scalar_t__ initiator; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 scalar_t__ NL80211_REGDOM_SET_BY_USER ; 
 struct ieee80211_regdomain const* get_cfg80211_regdom () ; 
 struct regulatory_request* get_last_request () ; 
 struct ieee80211_regdomain const* get_wiphy_regdom (struct wiphy*) ; 

__attribute__((used)) static const struct ieee80211_regdomain *reg_get_regdomain(struct wiphy *wiphy)
{
	struct regulatory_request *lr = get_last_request();

	/*
	 * Follow the driver's regulatory domain, if present, unless a country
	 * IE has been processed or a user wants to help complaince further
	 */
	if (lr->initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    lr->initiator != NL80211_REGDOM_SET_BY_USER &&
	    wiphy->regd)
		return get_wiphy_regdom(wiphy);

	return get_cfg80211_regdom();
}