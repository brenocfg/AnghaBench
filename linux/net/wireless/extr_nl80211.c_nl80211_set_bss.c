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
typedef  int u8 ;
struct wireless_dev {scalar_t__ iftype; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int features; } ;
struct net_device {struct wireless_dev* ieee80211_ptr; TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct genl_info {scalar_t__* attrs; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {struct wireless_dev* ieee80211_ptr; TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct bss_parameters {int use_cts_prot; int use_short_preamble; int use_short_slot_time; int ap_isolate; int ht_opmode; int p2p_ctwindow; int p2p_opp_ps; int /*<<< orphan*/  basic_rates_len; int /*<<< orphan*/  basic_rates; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int /*<<< orphan*/  change_bss; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL80211_ATTR_AP_ISOLATE ; 
 size_t NL80211_ATTR_BSS_BASIC_RATES ; 
 size_t NL80211_ATTR_BSS_CTS_PROT ; 
 size_t NL80211_ATTR_BSS_HT_OPMODE ; 
 size_t NL80211_ATTR_BSS_SHORT_PREAMBLE ; 
 size_t NL80211_ATTR_BSS_SHORT_SLOT_TIME ; 
 size_t NL80211_ATTR_P2P_CTWINDOW ; 
 size_t NL80211_ATTR_P2P_OPPPS ; 
 int NL80211_FEATURE_P2P_GO_CTWIN ; 
 int NL80211_FEATURE_P2P_GO_OPPPS ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  memset (struct bss_parameters*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int nla_get_u16 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int rdev_change_bss (struct net_device*,struct net_device*,struct bss_parameters*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_set_bss(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct bss_parameters params;
	int err;

	memset(&params, 0, sizeof(params));
	/* default to not changing parameters */
	params.use_cts_prot = -1;
	params.use_short_preamble = -1;
	params.use_short_slot_time = -1;
	params.ap_isolate = -1;
	params.ht_opmode = -1;
	params.p2p_ctwindow = -1;
	params.p2p_opp_ps = -1;

	if (info->attrs[NL80211_ATTR_BSS_CTS_PROT])
		params.use_cts_prot =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_CTS_PROT]);
	if (info->attrs[NL80211_ATTR_BSS_SHORT_PREAMBLE])
		params.use_short_preamble =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_SHORT_PREAMBLE]);
	if (info->attrs[NL80211_ATTR_BSS_SHORT_SLOT_TIME])
		params.use_short_slot_time =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_SHORT_SLOT_TIME]);
	if (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) {
		params.basic_rates =
			nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		params.basic_rates_len =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
	}
	if (info->attrs[NL80211_ATTR_AP_ISOLATE])
		params.ap_isolate = !!nla_get_u8(info->attrs[NL80211_ATTR_AP_ISOLATE]);
	if (info->attrs[NL80211_ATTR_BSS_HT_OPMODE])
		params.ht_opmode =
			nla_get_u16(info->attrs[NL80211_ATTR_BSS_HT_OPMODE]);

	if (info->attrs[NL80211_ATTR_P2P_CTWINDOW]) {
		if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
			return -EINVAL;
		params.p2p_ctwindow =
			nla_get_u8(info->attrs[NL80211_ATTR_P2P_CTWINDOW]);
		if (params.p2p_ctwindow != 0 &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_CTWIN))
			return -EINVAL;
	}

	if (info->attrs[NL80211_ATTR_P2P_OPPPS]) {
		u8 tmp;

		if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
			return -EINVAL;
		tmp = nla_get_u8(info->attrs[NL80211_ATTR_P2P_OPPPS]);
		params.p2p_opp_ps = tmp;
		if (params.p2p_opp_ps &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_OPPPS))
			return -EINVAL;
	}

	if (!rdev->ops->change_bss)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	wdev_lock(wdev);
	err = rdev_change_bss(rdev, dev, &params);
	wdev_unlock(wdev);

	return err;
}