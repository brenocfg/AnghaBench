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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int /*<<< orphan*/  owner_nlportid; TYPE_1__* netdev; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  wiphy_idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_nan_func_term_reason { ____Placeholder_nl80211_nan_func_term_reason } nl80211_nan_func_term_reason ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_COOKIE ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_NAN_FUNC ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_ATTR_WDEV ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_DEL_NAN_FUNCTION ; 
 int /*<<< orphan*/  NL80211_MCGRP_NAN ; 
 int /*<<< orphan*/  NL80211_NAN_FUNC_INSTANCE_ID ; 
 int /*<<< orphan*/  NL80211_NAN_FUNC_TERM_REASON ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_id (struct wireless_dev*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_nan_func_terminated(struct wireless_dev *wdev,
				  u8 inst_id,
				  enum nl80211_nan_func_term_reason reason,
				  u64 cookie, gfp_t gfp)
{
	struct wiphy *wiphy = wdev->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	struct sk_buff *msg;
	struct nlattr *func_attr;
	void *hdr;

	if (WARN_ON(!inst_id))
		return;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_DEL_NAN_FUNCTION);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					 wdev->netdev->ifindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		goto nla_put_failure;

	if (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		goto nla_put_failure;

	func_attr = nla_nest_start_noflag(msg, NL80211_ATTR_NAN_FUNC);
	if (!func_attr)
		goto nla_put_failure;

	if (nla_put_u8(msg, NL80211_NAN_FUNC_INSTANCE_ID, inst_id) ||
	    nla_put_u8(msg, NL80211_NAN_FUNC_TERM_REASON, reason))
		goto nla_put_failure;

	nla_nest_end(msg, func_attr);
	genlmsg_end(msg, hdr);

	if (!wdev->owner_nlportid)
		genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy),
					msg, 0, NL80211_MCGRP_NAN, gfp);
	else
		genlmsg_unicast(wiphy_net(&rdev->wiphy), msg,
				wdev->owner_nlportid);

	return;

nla_put_failure:
	nlmsg_free(msg);
}