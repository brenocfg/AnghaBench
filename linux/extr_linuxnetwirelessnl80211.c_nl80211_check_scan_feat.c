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
typedef  enum nl80211_ext_feature_index { ____Placeholder_nl80211_ext_feature_index } nl80211_ext_feature_index ;

/* Variables and functions */
 scalar_t__ wiphy_ext_feature_isset (struct wiphy*,int) ; 

__attribute__((used)) static bool nl80211_check_scan_feat(struct wiphy *wiphy, u32 flags, u32 flag,
				    enum nl80211_ext_feature_index feat)
{
	if (!(flags & flag))
		return true;
	if (wiphy_ext_feature_isset(wiphy, feat))
		return true;
	return false;
}