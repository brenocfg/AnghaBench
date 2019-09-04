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
struct TYPE_2__ {scalar_t__ link_state; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MAC80211_LINKED ; 
 int NL80211_IFTYPE_AP ; 
 scalar_t__ _rtl92se_set_media_status (struct ieee80211_hw*,int) ; 
 int /*<<< orphan*/  rtl92se_set_check_bssid (struct ieee80211_hw*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

int rtl92se_set_network_type(struct ieee80211_hw *hw, enum nl80211_iftype type)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (_rtl92se_set_media_status(hw, type))
		return -EOPNOTSUPP;

	if (rtlpriv->mac80211.link_state == MAC80211_LINKED) {
		if (type != NL80211_IFTYPE_AP)
			rtl92se_set_check_bssid(hw, true);
	} else {
		rtl92se_set_check_bssid(hw, false);
	}

	return 0;
}