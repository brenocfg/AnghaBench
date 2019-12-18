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
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NL80211_ATTR_FREQ_AFTER ; 
 int /*<<< orphan*/  NL80211_ATTR_FREQ_BEFORE ; 
 int /*<<< orphan*/  NL80211_ATTR_WIPHY ; 
 int /*<<< orphan*/  NL80211_CMD_REG_BEACON_HINT ; 
 int /*<<< orphan*/  NL80211_MCGRP_REGULATORY ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_allns (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_wiphy_idx (struct wiphy*) ; 
 int /*<<< orphan*/  nl80211_fam ; 
 scalar_t__ nl80211_msg_put_channel (struct sk_buff*,struct wiphy*,struct ieee80211_channel*,int) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void nl80211_send_beacon_hint_event(struct wiphy *wiphy,
				    struct ieee80211_channel *channel_before,
				    struct ieee80211_channel *channel_after)
{
	struct sk_buff *msg;
	void *hdr;
	struct nlattr *nl_freq;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_REG_BEACON_HINT);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	/*
	 * Since we are applying the beacon hint to a wiphy we know its
	 * wiphy_idx is valid
	 */
	if (nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
		goto nla_put_failure;

	/* Before */
	nl_freq = nla_nest_start_noflag(msg, NL80211_ATTR_FREQ_BEFORE);
	if (!nl_freq)
		goto nla_put_failure;

	if (nl80211_msg_put_channel(msg, wiphy, channel_before, false))
		goto nla_put_failure;
	nla_nest_end(msg, nl_freq);

	/* After */
	nl_freq = nla_nest_start_noflag(msg, NL80211_ATTR_FREQ_AFTER);
	if (!nl_freq)
		goto nla_put_failure;

	if (nl80211_msg_put_channel(msg, wiphy, channel_after, false))
		goto nla_put_failure;
	nla_nest_end(msg, nl_freq);

	genlmsg_end(msg, hdr);

	rcu_read_lock();
	genlmsg_multicast_allns(&nl80211_fam, msg, 0,
				NL80211_MCGRP_REGULATORY, GFP_ATOMIC);
	rcu_read_unlock();

	return;

nla_put_failure:
	nlmsg_free(msg);
}