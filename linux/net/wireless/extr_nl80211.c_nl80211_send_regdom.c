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
struct wiphy {int regulatory_flags; } ;
struct sk_buff {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/  skb; } ;
struct ieee80211_regdomain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_1__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_ATTR_USER_REG_HINT_TYPE ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY_SELF_MANAGED_REG ; 
 int /*<<< orphan*/  NL80211_CMD_GET_REG ; 
 int /*<<< orphan*/  NL80211_USER_REG_HINT_CELL_BASE ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 int /*<<< orphan*/  genl_dump_check_consistent (struct netlink_callback*,void*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  get_wiphy_idx (struct wiphy*) ; 
 scalar_t__ nl80211_put_regdom (struct ieee80211_regdomain const*,struct sk_buff*) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reg_last_request_cell_base () ; 

__attribute__((used)) static int nl80211_send_regdom(struct sk_buff *msg, struct netlink_callback *cb,
			       u32 seq, int flags, struct wiphy *wiphy,
			       const struct ieee80211_regdomain *regdom)
{
	void *hdr = nl80211hdr_put(msg, NETLINK_CB(cb->skb).portid, seq, flags,
				   NL80211_CMD_GET_REG);

	if (!hdr)
		return -1;

	genl_dump_check_consistent(cb, hdr);

	if (nl80211_put_regdom(regdom, msg))
		goto nla_put_failure;

	if (!wiphy && reg_last_request_cell_base() &&
	    nla_put_u32(msg, NL80211_ATTR_USER_REG_HINT_TYPE,
			NL80211_USER_REG_HINT_CELL_BASE))
		goto nla_put_failure;

	if (wiphy &&
	    nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
		goto nla_put_failure;

	if (wiphy && wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
	    nla_put_flag(msg, NL80211_ATTR_WIPHY_SELF_MANAGED_REG))
		goto nla_put_failure;

	genlmsg_end(msg, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}