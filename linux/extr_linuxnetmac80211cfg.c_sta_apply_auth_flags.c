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
typedef  int u32 ;
struct sta_info {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_STA_ASSOC ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTH ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTHORIZED ; 
 int /*<<< orphan*/  IEEE80211_STA_NONE ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_ASSOCIATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHENTICATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHORIZED ; 
 int /*<<< orphan*/  WLAN_STA_ASSOC ; 
 int /*<<< orphan*/  WLAN_STA_AUTH ; 
 int /*<<< orphan*/  WLAN_STA_AUTHORIZED ; 
 int /*<<< orphan*/  WLAN_STA_RATE_CONTROL ; 
 int /*<<< orphan*/  rate_control_rate_init (struct sta_info*) ; 
 int sta_info_move_state (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sta_apply_auth_flags(struct ieee80211_local *local,
				struct sta_info *sta,
				u32 mask, u32 set)
{
	int ret;

	if (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    set & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    !test_sta_flag(sta, WLAN_STA_AUTH)) {
		ret = sta_info_move_state(sta, IEEE80211_STA_AUTH);
		if (ret)
			return ret;
	}

	if (mask & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    set & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    !test_sta_flag(sta, WLAN_STA_ASSOC)) {
		/*
		 * When peer becomes associated, init rate control as
		 * well. Some drivers require rate control initialized
		 * before drv_sta_state() is called.
		 */
		if (!test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
			rate_control_rate_init(sta);

		ret = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
		if (ret)
			return ret;
	}

	if (mask & BIT(NL80211_STA_FLAG_AUTHORIZED)) {
		if (set & BIT(NL80211_STA_FLAG_AUTHORIZED))
			ret = sta_info_move_state(sta, IEEE80211_STA_AUTHORIZED);
		else if (test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			ret = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
		else
			ret = 0;
		if (ret)
			return ret;
	}

	if (mask & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    !(set & BIT(NL80211_STA_FLAG_ASSOCIATED)) &&
	    test_sta_flag(sta, WLAN_STA_ASSOC)) {
		ret = sta_info_move_state(sta, IEEE80211_STA_AUTH);
		if (ret)
			return ret;
	}

	if (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    !(set & BIT(NL80211_STA_FLAG_AUTHENTICATED)) &&
	    test_sta_flag(sta, WLAN_STA_AUTH)) {
		ret = sta_info_move_state(sta, IEEE80211_STA_NONE);
		if (ret)
			return ret;
	}

	return 0;
}