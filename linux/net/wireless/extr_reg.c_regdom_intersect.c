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
struct ieee80211_regdomain {unsigned int n_reg_rules; char* alpha2; int /*<<< orphan*/  dfs_region; struct ieee80211_reg_rule* reg_rules; } ;
struct ieee80211_reg_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_rule (struct ieee80211_reg_rule*,struct ieee80211_reg_rule*,unsigned int*) ; 
 struct ieee80211_regdomain* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_intersect_dfs_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_rules ; 
 int reg_rules_intersect (struct ieee80211_regdomain const*,struct ieee80211_regdomain const*,struct ieee80211_reg_rule const*,struct ieee80211_reg_rule const*,struct ieee80211_reg_rule*) ; 
 int /*<<< orphan*/  struct_size (struct ieee80211_regdomain*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct ieee80211_regdomain *
regdom_intersect(const struct ieee80211_regdomain *rd1,
		 const struct ieee80211_regdomain *rd2)
{
	int r;
	unsigned int x, y;
	unsigned int num_rules = 0;
	const struct ieee80211_reg_rule *rule1, *rule2;
	struct ieee80211_reg_rule intersected_rule;
	struct ieee80211_regdomain *rd;

	if (!rd1 || !rd2)
		return NULL;

	/*
	 * First we get a count of the rules we'll need, then we actually
	 * build them. This is to so we can malloc() and free() a
	 * regdomain once. The reason we use reg_rules_intersect() here
	 * is it will return -EINVAL if the rule computed makes no sense.
	 * All rules that do check out OK are valid.
	 */

	for (x = 0; x < rd1->n_reg_rules; x++) {
		rule1 = &rd1->reg_rules[x];
		for (y = 0; y < rd2->n_reg_rules; y++) {
			rule2 = &rd2->reg_rules[y];
			if (!reg_rules_intersect(rd1, rd2, rule1, rule2,
						 &intersected_rule))
				num_rules++;
		}
	}

	if (!num_rules)
		return NULL;

	rd = kzalloc(struct_size(rd, reg_rules, num_rules), GFP_KERNEL);
	if (!rd)
		return NULL;

	for (x = 0; x < rd1->n_reg_rules; x++) {
		rule1 = &rd1->reg_rules[x];
		for (y = 0; y < rd2->n_reg_rules; y++) {
			rule2 = &rd2->reg_rules[y];
			r = reg_rules_intersect(rd1, rd2, rule1, rule2,
						&intersected_rule);
			/*
			 * No need to memset here the intersected rule here as
			 * we're not using the stack anymore
			 */
			if (r)
				continue;

			add_rule(&intersected_rule, rd->reg_rules,
				 &rd->n_reg_rules);
		}
	}

	rd->alpha2[0] = '9';
	rd->alpha2[1] = '8';
	rd->dfs_region = reg_intersect_dfs_region(rd1->dfs_region,
						  rd2->dfs_region);

	return rd;
}