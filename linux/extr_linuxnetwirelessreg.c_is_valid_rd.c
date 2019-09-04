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
struct ieee80211_regdomain {unsigned int n_reg_rules; struct ieee80211_reg_rule* reg_rules; } ;
struct ieee80211_reg_rule {int dummy; } ;

/* Variables and functions */
 unsigned int NL80211_MAX_SUPP_REG_RULES ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  is_valid_reg_rule (struct ieee80211_reg_rule const*) ; 

__attribute__((used)) static bool is_valid_rd(const struct ieee80211_regdomain *rd)
{
	const struct ieee80211_reg_rule *reg_rule = NULL;
	unsigned int i;

	if (!rd->n_reg_rules)
		return false;

	if (WARN_ON(rd->n_reg_rules > NL80211_MAX_SUPP_REG_RULES))
		return false;

	for (i = 0; i < rd->n_reg_rules; i++) {
		reg_rule = &rd->reg_rules[i];
		if (!is_valid_reg_rule(reg_rule))
			return false;
	}

	return true;
}