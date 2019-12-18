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
struct wiphy {int dummy; } ;
struct cfg80211_chan_def {int /*<<< orphan*/  width; int /*<<< orphan*/  center_freq2; int /*<<< orphan*/  center_freq1; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  NL80211_IFTYPE_ADHOC 141 
#define  NL80211_IFTYPE_AP 140 
#define  NL80211_IFTYPE_AP_VLAN 139 
#define  NL80211_IFTYPE_MESH_POINT 138 
#define  NL80211_IFTYPE_MONITOR 137 
#define  NL80211_IFTYPE_NAN 136 
#define  NL80211_IFTYPE_OCB 135 
#define  NL80211_IFTYPE_P2P_CLIENT 134 
#define  NL80211_IFTYPE_P2P_DEVICE 133 
#define  NL80211_IFTYPE_P2P_GO 132 
#define  NL80211_IFTYPE_STATION 131 
#define  NL80211_IFTYPE_UNSPECIFIED 130 
#define  NL80211_IFTYPE_WDS 129 
#define  NUM_NL80211_IFTYPES 128 
 scalar_t__ WARN_ON (int) ; 
 int cfg80211_chandef_get_width (struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  cfg80211_chandef_valid (struct cfg80211_chan_def const*) ; 
 int cfg80211_get_chans_dfs_required (struct wiphy*,int /*<<< orphan*/ ,int) ; 

int cfg80211_chandef_dfs_required(struct wiphy *wiphy,
				  const struct cfg80211_chan_def *chandef,
				  enum nl80211_iftype iftype)
{
	int width;
	int ret;

	if (WARN_ON(!cfg80211_chandef_valid(chandef)))
		return -EINVAL;

	switch (iftype) {
	case NL80211_IFTYPE_ADHOC:
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_P2P_GO:
	case NL80211_IFTYPE_MESH_POINT:
		width = cfg80211_chandef_get_width(chandef);
		if (width < 0)
			return -EINVAL;

		ret = cfg80211_get_chans_dfs_required(wiphy,
						      chandef->center_freq1,
						      width);
		if (ret < 0)
			return ret;
		else if (ret > 0)
			return BIT(chandef->width);

		if (!chandef->center_freq2)
			return 0;

		ret = cfg80211_get_chans_dfs_required(wiphy,
						      chandef->center_freq2,
						      width);
		if (ret < 0)
			return ret;
		else if (ret > 0)
			return BIT(chandef->width);

		break;
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_OCB:
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_MONITOR:
	case NL80211_IFTYPE_AP_VLAN:
	case NL80211_IFTYPE_WDS:
	case NL80211_IFTYPE_P2P_DEVICE:
	case NL80211_IFTYPE_NAN:
		break;
	case NL80211_IFTYPE_UNSPECIFIED:
	case NUM_NL80211_IFTYPES:
		WARN_ON(1);
	}

	return 0;
}