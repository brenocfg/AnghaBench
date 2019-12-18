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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vif_params {int flags; int const* vht_mumimo_groups; void* vht_mumimo_follow_addr; } ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_2__ {int features; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int const BIT (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MONITOR_FLAG_ACTIVE ; 
 size_t NL80211_ATTR_MNTR_FLAGS ; 
 size_t NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR ; 
 size_t NL80211_ATTR_MU_MIMO_GROUP_DATA ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER ; 
 int NL80211_FEATURE_ACTIVE_MONITOR ; 
 int NL80211_IFTYPE_MONITOR ; 
 int VHT_MUMIMO_GROUPS_DATA_LEN ; 
 void* nla_data (scalar_t__) ; 
 int parse_monitor_flags (scalar_t__,int*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_parse_mon_options(struct cfg80211_registered_device *rdev,
				     enum nl80211_iftype type,
				     struct genl_info *info,
				     struct vif_params *params)
{
	bool change = false;
	int err;

	if (info->attrs[NL80211_ATTR_MNTR_FLAGS]) {
		if (type != NL80211_IFTYPE_MONITOR)
			return -EINVAL;

		err = parse_monitor_flags(info->attrs[NL80211_ATTR_MNTR_FLAGS],
					  &params->flags);
		if (err)
			return err;

		change = true;
	}

	if (params->flags & MONITOR_FLAG_ACTIVE &&
	    !(rdev->wiphy.features & NL80211_FEATURE_ACTIVE_MONITOR))
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_MU_MIMO_GROUP_DATA]) {
		const u8 *mumimo_groups;
		u32 cap_flag = NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER;

		if (type != NL80211_IFTYPE_MONITOR)
			return -EINVAL;

		if (!wiphy_ext_feature_isset(&rdev->wiphy, cap_flag))
			return -EOPNOTSUPP;

		mumimo_groups =
			nla_data(info->attrs[NL80211_ATTR_MU_MIMO_GROUP_DATA]);

		/* bits 0 and 63 are reserved and must be zero */
		if ((mumimo_groups[0] & BIT(0)) ||
		    (mumimo_groups[VHT_MUMIMO_GROUPS_DATA_LEN - 1] & BIT(7)))
			return -EINVAL;

		params->vht_mumimo_groups = mumimo_groups;
		change = true;
	}

	if (info->attrs[NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR]) {
		u32 cap_flag = NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER;

		if (type != NL80211_IFTYPE_MONITOR)
			return -EINVAL;

		if (!wiphy_ext_feature_isset(&rdev->wiphy, cap_flag))
			return -EOPNOTSUPP;

		params->vht_mumimo_follow_addr =
			nla_data(info->attrs[NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR]);
		change = true;
	}

	return change ? 1 : 0;
}