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
typedef  int /*<<< orphan*/  u32 ;
struct wireless_dev {TYPE_1__* netdev; } ;
struct sk_buff {scalar_t__ cb; } ;
struct nlattr {int dummy; } ;
struct nl80211_vendor_cmd_info {int /*<<< orphan*/  subcmd; int /*<<< orphan*/  vendor_id; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  wiphy_idx; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_commands { ____Placeholder_nl80211_commands } nl80211_commands ;
typedef  enum nl80211_attrs { ____Placeholder_nl80211_attrs } nl80211_attrs ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_PAD ; 
 int /*<<< orphan*/  NL80211_ATTR_VENDOR_ID ; 
 int /*<<< orphan*/  NL80211_ATTR_VENDOR_SUBCMD ; 
 int /*<<< orphan*/  NL80211_ATTR_WDEV ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdev_id (struct wireless_dev*) ; 

__attribute__((used)) static struct sk_buff *
__cfg80211_alloc_vendor_skb(struct cfg80211_registered_device *rdev,
			    struct wireless_dev *wdev, int approxlen,
			    u32 portid, u32 seq, enum nl80211_commands cmd,
			    enum nl80211_attrs attr,
			    const struct nl80211_vendor_cmd_info *info,
			    gfp_t gfp)
{
	struct sk_buff *skb;
	void *hdr;
	struct nlattr *data;

	skb = nlmsg_new(approxlen + 100, gfp);
	if (!skb)
		return NULL;

	hdr = nl80211hdr_put(skb, portid, seq, 0, cmd);
	if (!hdr) {
		kfree_skb(skb);
		return NULL;
	}

	if (nla_put_u32(skb, NL80211_ATTR_WIPHY, rdev->wiphy_idx))
		goto nla_put_failure;

	if (info) {
		if (nla_put_u32(skb, NL80211_ATTR_VENDOR_ID,
				info->vendor_id))
			goto nla_put_failure;
		if (nla_put_u32(skb, NL80211_ATTR_VENDOR_SUBCMD,
				info->subcmd))
			goto nla_put_failure;
	}

	if (wdev) {
		if (nla_put_u64_64bit(skb, NL80211_ATTR_WDEV,
				      wdev_id(wdev), NL80211_ATTR_PAD))
			goto nla_put_failure;
		if (wdev->netdev &&
		    nla_put_u32(skb, NL80211_ATTR_IFINDEX,
				wdev->netdev->ifindex))
			goto nla_put_failure;
	}

	data = nla_nest_start_noflag(skb, attr);
	if (!data)
		goto nla_put_failure;

	((void **)skb->cb)[0] = rdev;
	((void **)skb->cb)[1] = hdr;
	((void **)skb->cb)[2] = data;

	return skb;

 nla_put_failure:
	kfree_skb(skb);
	return NULL;
}