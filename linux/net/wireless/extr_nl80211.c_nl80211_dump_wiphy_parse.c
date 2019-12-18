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
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct nl80211_dump_wiphy_state {int filter_wiphy; struct nlattr* split; } ;
struct netlink_callback {int /*<<< orphan*/  nlh; } ;
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct cfg80211_registered_device {int wiphy_idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  maxattr; scalar_t__ hdrsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ GENL_HDRLEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NL80211_ATTR_IFINDEX ; 
 size_t NL80211_ATTR_SPLIT_WIPHY_DUMP ; 
 size_t NL80211_ATTR_WDEV ; 
 size_t NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NUM_NL80211_ATTR ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,int) ; 
 struct nlattr** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nlattr**) ; 
 TYPE_2__ nl80211_fam ; 
 int /*<<< orphan*/  nl80211_policy ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_get_u64 (struct nlattr*) ; 
 int nlmsg_parse_deprecated (int /*<<< orphan*/ ,scalar_t__,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 struct cfg80211_registered_device* wiphy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_dump_wiphy_parse(struct sk_buff *skb,
				    struct netlink_callback *cb,
				    struct nl80211_dump_wiphy_state *state)
{
	struct nlattr **tb = kcalloc(NUM_NL80211_ATTR, sizeof(*tb), GFP_KERNEL);
	int ret;

	if (!tb)
		return -ENOMEM;

	ret = nlmsg_parse_deprecated(cb->nlh,
				     GENL_HDRLEN + nl80211_fam.hdrsize,
				     tb, nl80211_fam.maxattr,
				     nl80211_policy, NULL);
	/* ignore parse errors for backward compatibility */
	if (ret) {
		ret = 0;
		goto out;
	}

	state->split = tb[NL80211_ATTR_SPLIT_WIPHY_DUMP];
	if (tb[NL80211_ATTR_WIPHY])
		state->filter_wiphy = nla_get_u32(tb[NL80211_ATTR_WIPHY]);
	if (tb[NL80211_ATTR_WDEV])
		state->filter_wiphy = nla_get_u64(tb[NL80211_ATTR_WDEV]) >> 32;
	if (tb[NL80211_ATTR_IFINDEX]) {
		struct net_device *netdev;
		struct cfg80211_registered_device *rdev;
		int ifidx = nla_get_u32(tb[NL80211_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(sock_net(skb->sk), ifidx);
		if (!netdev) {
			ret = -ENODEV;
			goto out;
		}
		if (netdev->ieee80211_ptr) {
			rdev = wiphy_to_rdev(
				netdev->ieee80211_ptr->wiphy);
			state->filter_wiphy = rdev->wiphy_idx;
		}
	}

	ret = 0;
out:
	kfree(tb);
	return ret;
}