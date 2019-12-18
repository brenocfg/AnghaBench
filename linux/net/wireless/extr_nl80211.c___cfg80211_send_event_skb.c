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
struct sk_buff {scalar_t__ cb; } ;
struct nlmsghdr {scalar_t__ nlmsg_pid; } ;
struct nlattr {scalar_t__ nla_type; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_multicast_groups { ____Placeholder_nl80211_multicast_groups } nl80211_multicast_groups ;

/* Variables and functions */
 scalar_t__ NL80211_ATTR_VENDOR_DATA ; 
 int NL80211_MCGRP_TESTMODE ; 
 int NL80211_MCGRP_VENDOR ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  wiphy_net (int /*<<< orphan*/ *) ; 

void __cfg80211_send_event_skb(struct sk_buff *skb, gfp_t gfp)
{
	struct cfg80211_registered_device *rdev = ((void **)skb->cb)[0];
	void *hdr = ((void **)skb->cb)[1];
	struct nlmsghdr *nlhdr = nlmsg_hdr(skb);
	struct nlattr *data = ((void **)skb->cb)[2];
	enum nl80211_multicast_groups mcgrp = NL80211_MCGRP_TESTMODE;

	/* clear CB data for netlink core to own from now on */
	memset(skb->cb, 0, sizeof(skb->cb));

	nla_nest_end(skb, data);
	genlmsg_end(skb, hdr);

	if (nlhdr->nlmsg_pid) {
		genlmsg_unicast(wiphy_net(&rdev->wiphy), skb,
				nlhdr->nlmsg_pid);
	} else {
		if (data->nla_type == NL80211_ATTR_VENDOR_DATA)
			mcgrp = NL80211_MCGRP_VENDOR;

		genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy),
					skb, 0, mcgrp, gfp);
	}
}