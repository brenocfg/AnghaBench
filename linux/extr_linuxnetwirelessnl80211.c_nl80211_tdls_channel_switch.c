#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wireless_dev {int iftype; int /*<<< orphan*/  wiphy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int features; } ;
struct net_device {TYPE_3__ wiphy; struct wireless_dev* ieee80211_ptr; TYPE_1__* ops; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {TYPE_3__ wiphy; struct wireless_dev* ieee80211_ptr; TYPE_1__* ops; } ;
struct cfg80211_chan_def {scalar_t__ width; TYPE_2__* chan; } ;
struct TYPE_5__ {scalar_t__ band; } ;
struct TYPE_4__ {int /*<<< orphan*/  tdls_channel_switch; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_MAC ; 
 size_t NL80211_ATTR_OPER_CLASS ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_CHAN_WIDTH_20 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int NL80211_FEATURE_TDLS_CHANNEL_SWITCH ; 
#define  NL80211_IFTYPE_P2P_CLIENT 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ cfg80211_chandef_dfs_required (int /*<<< orphan*/ ,struct cfg80211_chan_def*,int) ; 
 int /*<<< orphan*/  cfg80211_reg_can_beacon_relax (TYPE_3__*,struct cfg80211_chan_def*,int) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/ * nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u8 (int /*<<< orphan*/ ) ; 
 int rdev_tdls_channel_switch (struct net_device*,struct net_device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_tdls_channel_switch(struct sk_buff *skb,
				       struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct cfg80211_chan_def chandef = {};
	const u8 *addr;
	u8 oper_class;
	int err;

	if (!rdev->ops->tdls_channel_switch ||
	    !(rdev->wiphy.features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		return -EOPNOTSUPP;

	switch (dev->ieee80211_ptr->iftype) {
	case NL80211_IFTYPE_STATION:
	case NL80211_IFTYPE_P2P_CLIENT:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (!info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_OPER_CLASS])
		return -EINVAL;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	if (err)
		return err;

	/*
	 * Don't allow wide channels on the 2.4Ghz band, as per IEEE802.11-2012
	 * section 10.22.6.2.1. Disallow 5/10Mhz channels as well for now, the
	 * specification is not defined for them.
	 */
	if (chandef.chan->band == NL80211_BAND_2GHZ &&
	    chandef.width != NL80211_CHAN_WIDTH_20_NOHT &&
	    chandef.width != NL80211_CHAN_WIDTH_20)
		return -EINVAL;

	/* we will be active on the TDLS link */
	if (!cfg80211_reg_can_beacon_relax(&rdev->wiphy, &chandef,
					   wdev->iftype))
		return -EINVAL;

	/* don't allow switching to DFS channels */
	if (cfg80211_chandef_dfs_required(wdev->wiphy, &chandef, wdev->iftype))
		return -EINVAL;

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);
	oper_class = nla_get_u8(info->attrs[NL80211_ATTR_OPER_CLASS]);

	wdev_lock(wdev);
	err = rdev_tdls_channel_switch(rdev, dev, addr, oper_class, &chandef);
	wdev_unlock(wdev);

	return err;
}