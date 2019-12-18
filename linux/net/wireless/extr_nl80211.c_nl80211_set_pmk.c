#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {scalar_t__ iftype; TYPE_2__* current_bss; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  wiphy; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; struct wireless_dev* ieee80211_ptr; } ;
struct cfg80211_pmk_conf {scalar_t__ pmk_len; void* pmk_r0_name; void* pmk; void* aa; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_4__ {TYPE_1__ pub; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_PMK ; 
 size_t NL80211_ATTR_PMKR0_NAME ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X ; 
 scalar_t__ NL80211_IFTYPE_P2P_CLIENT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WLAN_PMK_LEN ; 
 scalar_t__ WLAN_PMK_LEN_SUITE_B_192 ; 
 int WLAN_PMK_NAME_LEN ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nla_data (scalar_t__) ; 
 void* nla_len (scalar_t__) ; 
 int rdev_set_pmk (struct net_device*,struct net_device*,struct cfg80211_pmk_conf*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_set_pmk(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_pmk_conf pmk_conf = {};
	int ret;

	if (wdev->iftype != NL80211_IFTYPE_STATION &&
	    wdev->iftype != NL80211_IFTYPE_P2P_CLIENT)
		return -EOPNOTSUPP;

	if (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X))
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_MAC] || !info->attrs[NL80211_ATTR_PMK])
		return -EINVAL;

	wdev_lock(wdev);
	if (!wdev->current_bss) {
		ret = -ENOTCONN;
		goto out;
	}

	pmk_conf.aa = nla_data(info->attrs[NL80211_ATTR_MAC]);
	if (memcmp(pmk_conf.aa, wdev->current_bss->pub.bssid, ETH_ALEN)) {
		ret = -EINVAL;
		goto out;
	}

	pmk_conf.pmk = nla_data(info->attrs[NL80211_ATTR_PMK]);
	pmk_conf.pmk_len = nla_len(info->attrs[NL80211_ATTR_PMK]);
	if (pmk_conf.pmk_len != WLAN_PMK_LEN &&
	    pmk_conf.pmk_len != WLAN_PMK_LEN_SUITE_B_192) {
		ret = -EINVAL;
		goto out;
	}

	if (info->attrs[NL80211_ATTR_PMKR0_NAME]) {
		int r0_name_len = nla_len(info->attrs[NL80211_ATTR_PMKR0_NAME]);

		if (r0_name_len != WLAN_PMK_NAME_LEN) {
			ret = -EINVAL;
			goto out;
		}

		pmk_conf.pmk_r0_name =
			nla_data(info->attrs[NL80211_ATTR_PMKR0_NAME]);
	}

	ret = rdev_set_pmk(rdev, dev, &pmk_conf);
out:
	wdev_unlock(wdev);
	return ret;
}