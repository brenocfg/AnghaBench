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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MONITOR_FLAG_CHANGED ; 
 int NL80211_MNTR_FLAG_MAX ; 
 int /*<<< orphan*/  mntr_flags_policy ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_monitor_flags(struct nlattr *nla, u32 *mntrflags)
{
	struct nlattr *flags[NL80211_MNTR_FLAG_MAX + 1];
	int flag;

	*mntrflags = 0;

	if (!nla)
		return -EINVAL;

	if (nla_parse_nested_deprecated(flags, NL80211_MNTR_FLAG_MAX, nla, mntr_flags_policy, NULL))
		return -EINVAL;

	for (flag = 1; flag <= NL80211_MNTR_FLAG_MAX; flag++)
		if (flags[flag])
			*mntrflags |= (1<<flag);

	*mntrflags |= MONITOR_FLAG_CHANGED;

	return 0;
}