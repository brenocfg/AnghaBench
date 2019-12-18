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
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ cfg80211_chandef_dfs_available (struct wiphy*,struct cfg80211_chan_def*) ; 
 scalar_t__ cfg80211_chandef_dfs_required (struct wiphy*,struct cfg80211_chan_def*,int) ; 
 int cfg80211_chandef_usable (struct wiphy*,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  trace_cfg80211_reg_can_beacon (struct wiphy*,struct cfg80211_chan_def*,int,int) ; 
 int /*<<< orphan*/  trace_cfg80211_return_bool (int) ; 

__attribute__((used)) static bool _cfg80211_reg_can_beacon(struct wiphy *wiphy,
				     struct cfg80211_chan_def *chandef,
				     enum nl80211_iftype iftype,
				     bool check_no_ir)
{
	bool res;
	u32 prohibited_flags = IEEE80211_CHAN_DISABLED |
			       IEEE80211_CHAN_RADAR;

	trace_cfg80211_reg_can_beacon(wiphy, chandef, iftype, check_no_ir);

	if (check_no_ir)
		prohibited_flags |= IEEE80211_CHAN_NO_IR;

	if (cfg80211_chandef_dfs_required(wiphy, chandef, iftype) > 0 &&
	    cfg80211_chandef_dfs_available(wiphy, chandef)) {
		/* We can skip IEEE80211_CHAN_NO_IR if chandef dfs available */
		prohibited_flags = IEEE80211_CHAN_DISABLED;
	}

	res = cfg80211_chandef_usable(wiphy, chandef, prohibited_flags);

	trace_cfg80211_return_bool(res);
	return res;
}