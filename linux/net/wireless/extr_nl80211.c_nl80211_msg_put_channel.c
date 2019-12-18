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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_reg_rule {scalar_t__ has_wmm; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  center_freq; int /*<<< orphan*/  max_power; int /*<<< orphan*/  dfs_cac_ms; int /*<<< orphan*/  dfs_state; int /*<<< orphan*/  dfs_state_entered; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBM_TO_MBM (int /*<<< orphan*/ ) ; 
 int ENOBUFS ; 
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_INDOOR_ONLY ; 
 int IEEE80211_CHAN_IR_CONCURRENT ; 
 int IEEE80211_CHAN_NO_10MHZ ; 
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_20MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ieee80211_reg_rule const*) ; 
 int /*<<< orphan*/  MHZ_TO_KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_DFS_CAC_TIME ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_DFS_STATE ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_DFS_TIME ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_DISABLED ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_FREQ ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_INDOOR_ONLY ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_IR_CONCURRENT ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_MAX_TX_POWER ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_10MHZ ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_160MHZ ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_20MHZ ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_80MHZ ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_HT40_MINUS ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_HT40_PLUS ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_NO_IR ; 
 int /*<<< orphan*/  NL80211_FREQUENCY_ATTR_RADAR ; 
 int /*<<< orphan*/  __NL80211_FREQUENCY_ATTR_NO_IBSS ; 
 int /*<<< orphan*/  elapsed_jiffies_msecs (int /*<<< orphan*/ ) ; 
 struct ieee80211_reg_rule* freq_reg_info (struct wiphy*,int /*<<< orphan*/ ) ; 
 scalar_t__ nl80211_msg_put_wmm_rules (struct sk_buff*,struct ieee80211_reg_rule const*) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_msg_put_channel(struct sk_buff *msg, struct wiphy *wiphy,
				   struct ieee80211_channel *chan,
				   bool large)
{
	/* Some channels must be completely excluded from the
	 * list to protect old user-space tools from breaking
	 */
	if (!large && chan->flags &
	    (IEEE80211_CHAN_NO_10MHZ | IEEE80211_CHAN_NO_20MHZ))
		return 0;

	if (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_FREQ,
			chan->center_freq))
		goto nla_put_failure;

	if ((chan->flags & IEEE80211_CHAN_DISABLED) &&
	    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_DISABLED))
		goto nla_put_failure;
	if (chan->flags & IEEE80211_CHAN_NO_IR) {
		if (nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_IR))
			goto nla_put_failure;
		if (nla_put_flag(msg, __NL80211_FREQUENCY_ATTR_NO_IBSS))
			goto nla_put_failure;
	}
	if (chan->flags & IEEE80211_CHAN_RADAR) {
		if (nla_put_flag(msg, NL80211_FREQUENCY_ATTR_RADAR))
			goto nla_put_failure;
		if (large) {
			u32 time;

			time = elapsed_jiffies_msecs(chan->dfs_state_entered);

			if (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_DFS_STATE,
					chan->dfs_state))
				goto nla_put_failure;
			if (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_DFS_TIME,
					time))
				goto nla_put_failure;
			if (nla_put_u32(msg,
					NL80211_FREQUENCY_ATTR_DFS_CAC_TIME,
					chan->dfs_cac_ms))
				goto nla_put_failure;
		}
	}

	if (large) {
		if ((chan->flags & IEEE80211_CHAN_NO_HT40MINUS) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_HT40_MINUS))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_NO_HT40PLUS) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_HT40_PLUS))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_NO_80MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_80MHZ))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_NO_160MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_160MHZ))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_INDOOR_ONLY) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_INDOOR_ONLY))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_IR_CONCURRENT) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_IR_CONCURRENT))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_NO_20MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_20MHZ))
			goto nla_put_failure;
		if ((chan->flags & IEEE80211_CHAN_NO_10MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_10MHZ))
			goto nla_put_failure;
	}

	if (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_MAX_TX_POWER,
			DBM_TO_MBM(chan->max_power)))
		goto nla_put_failure;

	if (large) {
		const struct ieee80211_reg_rule *rule =
			freq_reg_info(wiphy, MHZ_TO_KHZ(chan->center_freq));

		if (!IS_ERR_OR_NULL(rule) && rule->has_wmm) {
			if (nl80211_msg_put_wmm_rules(msg, rule))
				goto nla_put_failure;
		}
	}

	return 0;

 nla_put_failure:
	return -ENOBUFS;
}