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
typedef  size_t u32 ;
struct ieee80211_regdomain {size_t n_reg_rules; struct ieee80211_reg_rule const* reg_rules; } ;
struct ieee80211_freq_range {scalar_t__ end_freq_khz; scalar_t__ start_freq_khz; } ;
typedef  struct ieee80211_reg_rule {struct ieee80211_freq_range freq_range; } const ieee80211_reg_rule ;

/* Variables and functions */

__attribute__((used)) static unsigned int
reg_get_max_bandwidth_from_range(const struct ieee80211_regdomain *rd,
				 const struct ieee80211_reg_rule *rule)
{
	const struct ieee80211_freq_range *freq_range = &rule->freq_range;
	const struct ieee80211_freq_range *freq_range_tmp;
	const struct ieee80211_reg_rule *tmp;
	u32 start_freq, end_freq, idx, no;

	for (idx = 0; idx < rd->n_reg_rules; idx++)
		if (rule == &rd->reg_rules[idx])
			break;

	if (idx == rd->n_reg_rules)
		return 0;

	/* get start_freq */
	no = idx;

	while (no) {
		tmp = &rd->reg_rules[--no];
		freq_range_tmp = &tmp->freq_range;

		if (freq_range_tmp->end_freq_khz < freq_range->start_freq_khz)
			break;

		freq_range = freq_range_tmp;
	}

	start_freq = freq_range->start_freq_khz;

	/* get end_freq */
	freq_range = &rule->freq_range;
	no = idx;

	while (no < rd->n_reg_rules - 1) {
		tmp = &rd->reg_rules[++no];
		freq_range_tmp = &tmp->freq_range;

		if (freq_range_tmp->start_freq_khz > freq_range->end_freq_khz)
			break;

		freq_range = freq_range_tmp;
	}

	end_freq = freq_range->end_freq_khz;

	return end_freq - start_freq;
}