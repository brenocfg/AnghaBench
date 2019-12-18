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
typedef  int u32 ;
struct ieee80211_reg_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ieee80211_reg_rule*,struct ieee80211_reg_rule*,int) ; 
 scalar_t__ rule_contains (struct ieee80211_reg_rule*,struct ieee80211_reg_rule*) ; 

__attribute__((used)) static void add_rule(struct ieee80211_reg_rule *rule,
		     struct ieee80211_reg_rule *reg_rules, u32 *n_rules)
{
	struct ieee80211_reg_rule *tmp_rule;
	int i;

	for (i = 0; i < *n_rules; i++) {
		tmp_rule = &reg_rules[i];
		/* rule is already contained - do nothing */
		if (rule_contains(tmp_rule, rule))
			return;

		/* extend rule if possible */
		if (rule_contains(rule, tmp_rule)) {
			memcpy(tmp_rule, rule, sizeof(*rule));
			return;
		}
	}

	memcpy(&reg_rules[*n_rules], rule, sizeof(*rule));
	(*n_rules)++;
}