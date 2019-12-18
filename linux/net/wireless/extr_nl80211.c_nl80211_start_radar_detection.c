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
struct cfg80211_chan_def {int dummy; } ;
struct wireless_dev {int cac_started; unsigned int cac_time_ms; int /*<<< orphan*/  cac_start_time; struct cfg80211_chan_def chandef; int /*<<< orphan*/  iftype; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;
struct TYPE_2__ {int /*<<< orphan*/  start_radar_detection; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 unsigned int IEEE80211_DFS_MIN_CAC_TIME_MS ; 
 int NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_DFS_OFFLOAD ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int cfg80211_chandef_dfs_cac_time (int /*<<< orphan*/ *,struct cfg80211_chan_def*) ; 
 int cfg80211_chandef_dfs_required (struct wiphy*,struct cfg80211_chan_def*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_chandef_dfs_usable (struct wiphy*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,struct cfg80211_chan_def*) ; 
 int rdev_start_radar_detection (struct net_device*,struct net_device*,struct cfg80211_chan_def*,unsigned int) ; 
 int reg_get_dfs_region (struct wiphy*) ; 
 scalar_t__ wiphy_ext_feature_isset (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_start_radar_detection(struct sk_buff *skb,
					 struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_chan_def chandef;
	enum nl80211_dfs_regions dfs_region;
	unsigned int cac_time_ms;
	int err;

	dfs_region = reg_get_dfs_region(wiphy);
	if (dfs_region == NL80211_DFS_UNSET)
		return -EINVAL;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	if (err)
		return err;

	if (netif_carrier_ok(dev))
		return -EBUSY;

	if (wdev->cac_started)
		return -EBUSY;

	err = cfg80211_chandef_dfs_required(wiphy, &chandef, wdev->iftype);
	if (err < 0)
		return err;

	if (err == 0)
		return -EINVAL;

	if (!cfg80211_chandef_dfs_usable(wiphy, &chandef))
		return -EINVAL;

	/* CAC start is offloaded to HW and can't be started manually */
	if (wiphy_ext_feature_isset(wiphy, NL80211_EXT_FEATURE_DFS_OFFLOAD))
		return -EOPNOTSUPP;

	if (!rdev->ops->start_radar_detection)
		return -EOPNOTSUPP;

	cac_time_ms = cfg80211_chandef_dfs_cac_time(&rdev->wiphy, &chandef);
	if (WARN_ON(!cac_time_ms))
		cac_time_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;

	err = rdev_start_radar_detection(rdev, dev, &chandef, cac_time_ms);
	if (!err) {
		wdev->chandef = chandef;
		wdev->cac_started = true;
		wdev->cac_start_time = jiffies;
		wdev->cac_time_ms = cac_time_ms;
	}
	return err;
}