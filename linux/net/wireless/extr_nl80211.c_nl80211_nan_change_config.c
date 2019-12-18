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
typedef  int u32 ;
struct wireless_dev {scalar_t__ iftype; TYPE_1__* wiphy; } ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ iftype; TYPE_1__* wiphy; } ;
struct cfg80211_nan_conf {int master_pref; int bands; } ;
struct TYPE_2__ {scalar_t__ nan_supported_bands; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CFG80211_NAN_CONF_CHANGED_BANDS ; 
 int CFG80211_NAN_CONF_CHANGED_PREF ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_BANDS ; 
 size_t NL80211_ATTR_NAN_MASTER_PREF ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_IFTYPE_NAN ; 
 int nla_get_u32 (scalar_t__) ; 
 int nla_get_u8 (scalar_t__) ; 
 int rdev_nan_change_conf (struct wireless_dev*,struct wireless_dev*,struct cfg80211_nan_conf*,int) ; 
 int /*<<< orphan*/  wdev_running (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_nan_change_config(struct sk_buff *skb,
				     struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	struct cfg80211_nan_conf conf = {};
	u32 changed = 0;

	if (wdev->iftype != NL80211_IFTYPE_NAN)
		return -EOPNOTSUPP;

	if (!wdev_running(wdev))
		return -ENOTCONN;

	if (info->attrs[NL80211_ATTR_NAN_MASTER_PREF]) {
		conf.master_pref =
			nla_get_u8(info->attrs[NL80211_ATTR_NAN_MASTER_PREF]);
		if (conf.master_pref <= 1 || conf.master_pref == 255)
			return -EINVAL;

		changed |= CFG80211_NAN_CONF_CHANGED_PREF;
	}

	if (info->attrs[NL80211_ATTR_BANDS]) {
		u32 bands = nla_get_u32(info->attrs[NL80211_ATTR_BANDS]);

		if (bands & ~(u32)wdev->wiphy->nan_supported_bands)
			return -EOPNOTSUPP;

		if (bands && !(bands & BIT(NL80211_BAND_2GHZ)))
			return -EINVAL;

		conf.bands = bands;
		changed |= CFG80211_NAN_CONF_CHANGED_BANDS;
	}

	if (!changed)
		return -EINVAL;

	return rdev_nan_change_conf(rdev, wdev, &conf, changed);
}