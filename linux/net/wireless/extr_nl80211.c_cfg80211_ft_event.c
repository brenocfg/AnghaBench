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
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; TYPE_1__* ieee80211_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  wiphy_idx; } ;
struct cfg80211_ft_event_params {scalar_t__ ric_ies; scalar_t__ ric_ies_len; scalar_t__ ies; scalar_t__ ies_len; scalar_t__ target_ap; } ;
struct TYPE_2__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_ATTR_IE ; 
 int /*<<< orphan*/  NL80211_ATTR_IE_RIC ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_FT_EVENT ; 
 int /*<<< orphan*/  NL80211_MCGRP_MLME ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_cfg80211_ft_event (struct wiphy*,struct net_device*,struct cfg80211_ft_event_params*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (struct wiphy*) ; 

void cfg80211_ft_event(struct net_device *netdev,
		       struct cfg80211_ft_event_params *ft_event)
{
	struct wiphy *wiphy = netdev->ieee80211_ptr->wiphy;
	struct cfg80211_registered_device *rdev = wiphy_to_rdev(wiphy);
	struct sk_buff *msg;
	void *hdr;

	trace_cfg80211_ft_event(wiphy, netdev, ft_event);

	if (!ft_event->target_ap)
		return;

	msg = nlmsg_new(100 + ft_event->ies_len + ft_event->ric_ies_len,
			GFP_KERNEL);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FT_EVENT);
	if (!hdr)
		goto out;

	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->ifindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, ft_event->target_ap))
		goto out;

	if (ft_event->ies &&
	    nla_put(msg, NL80211_ATTR_IE, ft_event->ies_len, ft_event->ies))
		goto out;
	if (ft_event->ric_ies &&
	    nla_put(msg, NL80211_ATTR_IE_RIC, ft_event->ric_ies_len,
		    ft_event->ric_ies))
		goto out;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, GFP_KERNEL);
	return;
 out:
	nlmsg_free(msg);
}