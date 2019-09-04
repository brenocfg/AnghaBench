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
typedef  scalar_t__ u32 ;
struct ieee80211_regdomain {int dummy; } ;
struct ieee80211_power_rule {scalar_t__ max_eirp; scalar_t__ max_antenna_gain; } ;
struct ieee80211_freq_range {scalar_t__ start_freq_khz; scalar_t__ end_freq_khz; scalar_t__ max_bandwidth_khz; } ;
struct ieee80211_reg_rule {int flags; scalar_t__ dfs_cac_ms; struct ieee80211_power_rule power_rule; struct ieee80211_freq_range freq_range; } ;

/* Variables and functions */
 int EINVAL ; 
 int NL80211_RRF_AUTO_BW ; 
 int /*<<< orphan*/  is_valid_reg_rule (struct ieee80211_reg_rule*) ; 
 void* max (scalar_t__,scalar_t__) ; 
 void* min (scalar_t__,scalar_t__) ; 
 scalar_t__ reg_get_max_bandwidth (struct ieee80211_regdomain const*,struct ieee80211_reg_rule const*) ; 

__attribute__((used)) static int reg_rules_intersect(const struct ieee80211_regdomain *rd1,
			       const struct ieee80211_regdomain *rd2,
			       const struct ieee80211_reg_rule *rule1,
			       const struct ieee80211_reg_rule *rule2,
			       struct ieee80211_reg_rule *intersected_rule)
{
	const struct ieee80211_freq_range *freq_range1, *freq_range2;
	struct ieee80211_freq_range *freq_range;
	const struct ieee80211_power_rule *power_rule1, *power_rule2;
	struct ieee80211_power_rule *power_rule;
	u32 freq_diff, max_bandwidth1, max_bandwidth2;

	freq_range1 = &rule1->freq_range;
	freq_range2 = &rule2->freq_range;
	freq_range = &intersected_rule->freq_range;

	power_rule1 = &rule1->power_rule;
	power_rule2 = &rule2->power_rule;
	power_rule = &intersected_rule->power_rule;

	freq_range->start_freq_khz = max(freq_range1->start_freq_khz,
					 freq_range2->start_freq_khz);
	freq_range->end_freq_khz = min(freq_range1->end_freq_khz,
				       freq_range2->end_freq_khz);

	max_bandwidth1 = freq_range1->max_bandwidth_khz;
	max_bandwidth2 = freq_range2->max_bandwidth_khz;

	if (rule1->flags & NL80211_RRF_AUTO_BW)
		max_bandwidth1 = reg_get_max_bandwidth(rd1, rule1);
	if (rule2->flags & NL80211_RRF_AUTO_BW)
		max_bandwidth2 = reg_get_max_bandwidth(rd2, rule2);

	freq_range->max_bandwidth_khz = min(max_bandwidth1, max_bandwidth2);

	intersected_rule->flags = rule1->flags | rule2->flags;

	/*
	 * In case NL80211_RRF_AUTO_BW requested for both rules
	 * set AUTO_BW in intersected rule also. Next we will
	 * calculate BW correctly in handle_channel function.
	 * In other case remove AUTO_BW flag while we calculate
	 * maximum bandwidth correctly and auto calculation is
	 * not required.
	 */
	if ((rule1->flags & NL80211_RRF_AUTO_BW) &&
	    (rule2->flags & NL80211_RRF_AUTO_BW))
		intersected_rule->flags |= NL80211_RRF_AUTO_BW;
	else
		intersected_rule->flags &= ~NL80211_RRF_AUTO_BW;

	freq_diff = freq_range->end_freq_khz - freq_range->start_freq_khz;
	if (freq_range->max_bandwidth_khz > freq_diff)
		freq_range->max_bandwidth_khz = freq_diff;

	power_rule->max_eirp = min(power_rule1->max_eirp,
		power_rule2->max_eirp);
	power_rule->max_antenna_gain = min(power_rule1->max_antenna_gain,
		power_rule2->max_antenna_gain);

	intersected_rule->dfs_cac_ms = max(rule1->dfs_cac_ms,
					   rule2->dfs_cac_ms);

	if (!is_valid_reg_rule(intersected_rule))
		return -EINVAL;

	return 0;
}