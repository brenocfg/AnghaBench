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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct wireless_dev {int iftype; int /*<<< orphan*/  current_bss; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int features; } ;
struct net_device {TYPE_1__ wiphy; struct wireless_dev* ieee80211_ptr; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; struct wireless_dev* ieee80211_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ IEEE80211_FIRST_TSPEC_TSID ; 
 size_t NL80211_ATTR_ADMITTED_TIME ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_TSID ; 
 size_t NL80211_ATTR_USER_PRIO ; 
 int NL80211_FEATURE_SUPPORTS_WMM_ADMISSION ; 
#define  NL80211_IFTYPE_P2P_CLIENT 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__* nla_data (scalar_t__) ; 
 scalar_t__ nla_get_u16 (scalar_t__) ; 
 scalar_t__ nla_get_u8 (scalar_t__) ; 
 int rdev_add_tx_ts (struct net_device*,struct net_device*,scalar_t__,scalar_t__ const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_add_tx_ts(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	const u8 *peer;
	u8 tsid, up;
	u16 admitted_time = 0;
	int err;

	if (!(rdev->wiphy.features & NL80211_FEATURE_SUPPORTS_WMM_ADMISSION))
		return -EOPNOTSUPP;

	if (!info->attrs[NL80211_ATTR_TSID] || !info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_USER_PRIO])
		return -EINVAL;

	tsid = nla_get_u8(info->attrs[NL80211_ATTR_TSID]);
	up = nla_get_u8(info->attrs[NL80211_ATTR_USER_PRIO]);

	/* WMM uses TIDs 0-7 even for TSPEC */
	if (tsid >= IEEE80211_FIRST_TSPEC_TSID) {
		/* TODO: handle 802.11 TSPEC/admission control
		 * need more attributes for that (e.g. BA session requirement);
		 * change the WMM adminssion test above to allow both then
		 */
		return -EINVAL;
	}

	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);

	if (info->attrs[NL80211_ATTR_ADMITTED_TIME]) {
		admitted_time =
			nla_get_u16(info->attrs[NL80211_ATTR_ADMITTED_TIME]);
		if (!admitted_time)
			return -EINVAL;
	}

	wdev_lock(wdev);
	switch (wdev->iftype) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		if (wdev->current_bss)
			break;
		err = -ENOTCONN;
		goto out;
	default:
		err = -EOPNOTSUPP;
		goto out;
	}

	err = rdev_add_tx_ts(rdev, dev, tsid, peer, up, admitted_time);

 out:
	wdev_unlock(wdev);
	return err;
}