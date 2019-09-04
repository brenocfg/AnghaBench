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
struct ieee80211_regdomain {int n_reg_rules; struct ieee80211_reg_rule* reg_rules; } ;
struct ieee80211_freq_range {int dummy; } ;
struct ieee80211_reg_rule {struct ieee80211_freq_range freq_range; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 struct ieee80211_reg_rule const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int cfg80211_does_bw_fit_range (struct ieee80211_freq_range const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int freq_in_rule_band (struct ieee80211_freq_range const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct ieee80211_reg_rule *
freq_reg_info_regd(u32 center_freq,
		   const struct ieee80211_regdomain *regd, u32 bw)
{
	int i;
	bool band_rule_found = false;
	bool bw_fits = false;

	if (!regd)
		return ERR_PTR(-EINVAL);

	for (i = 0; i < regd->n_reg_rules; i++) {
		const struct ieee80211_reg_rule *rr;
		const struct ieee80211_freq_range *fr = NULL;

		rr = &regd->reg_rules[i];
		fr = &rr->freq_range;

		/*
		 * We only need to know if one frequency rule was
		 * was in center_freq's band, that's enough, so lets
		 * not overwrite it once found
		 */
		if (!band_rule_found)
			band_rule_found = freq_in_rule_band(fr, center_freq);

		bw_fits = cfg80211_does_bw_fit_range(fr, center_freq, bw);

		if (band_rule_found && bw_fits)
			return rr;
	}

	if (!band_rule_found)
		return ERR_PTR(-ERANGE);

	return ERR_PTR(-EINVAL);
}