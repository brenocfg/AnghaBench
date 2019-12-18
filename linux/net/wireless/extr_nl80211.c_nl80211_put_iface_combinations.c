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
struct wiphy {int n_iface_combinations; struct ieee80211_iface_combination* iface_combinations; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct ieee80211_iface_combination {int n_limits; scalar_t__ beacon_int_min_gcd; scalar_t__ radar_detect_regions; scalar_t__ radar_detect_widths; scalar_t__ max_interfaces; scalar_t__ num_different_channels; scalar_t__ beacon_int_infra_match; TYPE_1__* limits; } ;
struct TYPE_2__ {int /*<<< orphan*/  types; scalar_t__ max; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int NL80211_ATTR_INTERFACE_COMBINATIONS ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_BI_MIN_GCD ; 
 int NL80211_IFACE_COMB_LIMITS ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_MAXNUM ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_NUM_CHANNELS ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_RADAR_DETECT_REGIONS ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_RADAR_DETECT_WIDTHS ; 
 int /*<<< orphan*/  NL80211_IFACE_COMB_STA_AP_BI_MATCH ; 
 int /*<<< orphan*/  NL80211_IFACE_LIMIT_MAX ; 
 int /*<<< orphan*/  NL80211_IFACE_LIMIT_TYPES ; 
 scalar_t__ nl80211_put_iftypes (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nl80211_put_iface_combinations(struct wiphy *wiphy,
					  struct sk_buff *msg,
					  bool large)
{
	struct nlattr *nl_combis;
	int i, j;

	nl_combis = nla_nest_start_noflag(msg,
					  NL80211_ATTR_INTERFACE_COMBINATIONS);
	if (!nl_combis)
		goto nla_put_failure;

	for (i = 0; i < wiphy->n_iface_combinations; i++) {
		const struct ieee80211_iface_combination *c;
		struct nlattr *nl_combi, *nl_limits;

		c = &wiphy->iface_combinations[i];

		nl_combi = nla_nest_start_noflag(msg, i + 1);
		if (!nl_combi)
			goto nla_put_failure;

		nl_limits = nla_nest_start_noflag(msg,
						  NL80211_IFACE_COMB_LIMITS);
		if (!nl_limits)
			goto nla_put_failure;

		for (j = 0; j < c->n_limits; j++) {
			struct nlattr *nl_limit;

			nl_limit = nla_nest_start_noflag(msg, j + 1);
			if (!nl_limit)
				goto nla_put_failure;
			if (nla_put_u32(msg, NL80211_IFACE_LIMIT_MAX,
					c->limits[j].max))
				goto nla_put_failure;
			if (nl80211_put_iftypes(msg, NL80211_IFACE_LIMIT_TYPES,
						c->limits[j].types))
				goto nla_put_failure;
			nla_nest_end(msg, nl_limit);
		}

		nla_nest_end(msg, nl_limits);

		if (c->beacon_int_infra_match &&
		    nla_put_flag(msg, NL80211_IFACE_COMB_STA_AP_BI_MATCH))
			goto nla_put_failure;
		if (nla_put_u32(msg, NL80211_IFACE_COMB_NUM_CHANNELS,
				c->num_different_channels) ||
		    nla_put_u32(msg, NL80211_IFACE_COMB_MAXNUM,
				c->max_interfaces))
			goto nla_put_failure;
		if (large &&
		    (nla_put_u32(msg, NL80211_IFACE_COMB_RADAR_DETECT_WIDTHS,
				c->radar_detect_widths) ||
		     nla_put_u32(msg, NL80211_IFACE_COMB_RADAR_DETECT_REGIONS,
				c->radar_detect_regions)))
			goto nla_put_failure;
		if (c->beacon_int_min_gcd &&
		    nla_put_u32(msg, NL80211_IFACE_COMB_BI_MIN_GCD,
				c->beacon_int_min_gcd))
			goto nla_put_failure;

		nla_nest_end(msg, nl_combi);
	}

	nla_nest_end(msg, nl_combis);

	return 0;
nla_put_failure:
	return -ENOBUFS;
}