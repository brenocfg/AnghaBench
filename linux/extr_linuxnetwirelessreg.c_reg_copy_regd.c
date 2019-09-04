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
typedef  struct ieee80211_regdomain {int n_reg_rules; struct ieee80211_regdomain const* reg_rules; } const ieee80211_regdomain ;
struct ieee80211_reg_rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ieee80211_regdomain const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ieee80211_regdomain const* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_regdomain const*,struct ieee80211_regdomain const*,int) ; 

__attribute__((used)) static const struct ieee80211_regdomain *
reg_copy_regd(const struct ieee80211_regdomain *src_regd)
{
	struct ieee80211_regdomain *regd;
	int size_of_regd;
	unsigned int i;

	size_of_regd =
		sizeof(struct ieee80211_regdomain) +
		src_regd->n_reg_rules * sizeof(struct ieee80211_reg_rule);

	regd = kzalloc(size_of_regd, GFP_KERNEL);
	if (!regd)
		return ERR_PTR(-ENOMEM);

	memcpy(regd, src_regd, sizeof(struct ieee80211_regdomain));

	for (i = 0; i < src_regd->n_reg_rules; i++)
		memcpy(&regd->reg_rules[i], &src_regd->reg_rules[i],
		       sizeof(struct ieee80211_reg_rule));

	return regd;
}