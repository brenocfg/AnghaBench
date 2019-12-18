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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {TYPE_1__* client; } ;
struct ieee80211_reg_rule {TYPE_2__ wmm_rule; } ;
struct TYPE_3__ {int /*<<< orphan*/  cot; int /*<<< orphan*/  aifsn; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int IEEE80211_NUM_ACS ; 
 int NL80211_FREQUENCY_ATTR_WMM ; 
 int /*<<< orphan*/  NL80211_WMMR_AIFSN ; 
 int /*<<< orphan*/  NL80211_WMMR_CW_MAX ; 
 int /*<<< orphan*/  NL80211_WMMR_CW_MIN ; 
 int /*<<< orphan*/  NL80211_WMMR_TXOP ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_msg_put_wmm_rules(struct sk_buff *msg,
				     const struct ieee80211_reg_rule *rule)
{
	int j;
	struct nlattr *nl_wmm_rules =
		nla_nest_start_noflag(msg, NL80211_FREQUENCY_ATTR_WMM);

	if (!nl_wmm_rules)
		goto nla_put_failure;

	for (j = 0; j < IEEE80211_NUM_ACS; j++) {
		struct nlattr *nl_wmm_rule = nla_nest_start_noflag(msg, j);

		if (!nl_wmm_rule)
			goto nla_put_failure;

		if (nla_put_u16(msg, NL80211_WMMR_CW_MIN,
				rule->wmm_rule.client[j].cw_min) ||
		    nla_put_u16(msg, NL80211_WMMR_CW_MAX,
				rule->wmm_rule.client[j].cw_max) ||
		    nla_put_u8(msg, NL80211_WMMR_AIFSN,
			       rule->wmm_rule.client[j].aifsn) ||
		    nla_put_u16(msg, NL80211_WMMR_TXOP,
			        rule->wmm_rule.client[j].cot))
			goto nla_put_failure;

		nla_nest_end(msg, nl_wmm_rule);
	}
	nla_nest_end(msg, nl_wmm_rules);

	return 0;

nla_put_failure:
	return -ENOBUFS;
}