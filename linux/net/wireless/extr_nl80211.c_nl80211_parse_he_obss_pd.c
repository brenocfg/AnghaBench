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
struct nlattr {int dummy; } ;
struct ieee80211_he_obss_pd {scalar_t__ min_offset; scalar_t__ max_offset; int enable; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL80211_HE_OBSS_PD_ATTR_MAX ; 
 size_t NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET ; 
 size_t NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET ; 
 int /*<<< orphan*/  he_obss_pd_policy ; 
 void* nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_parse_he_obss_pd(struct nlattr *attrs,
				    struct ieee80211_he_obss_pd *he_obss_pd)
{
	struct nlattr *tb[NL80211_HE_OBSS_PD_ATTR_MAX + 1];
	int err;

	err = nla_parse_nested(tb, NL80211_HE_OBSS_PD_ATTR_MAX, attrs,
			       he_obss_pd_policy, NULL);
	if (err)
		return err;

	if (!tb[NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET] ||
	    !tb[NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET])
		return -EINVAL;

	he_obss_pd->min_offset =
		nla_get_u32(tb[NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET]);
	he_obss_pd->max_offset =
		nla_get_u32(tb[NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET]);

	if (he_obss_pd->min_offset >= he_obss_pd->max_offset)
		return -EINVAL;

	he_obss_pd->enable = true;

	return 0;
}