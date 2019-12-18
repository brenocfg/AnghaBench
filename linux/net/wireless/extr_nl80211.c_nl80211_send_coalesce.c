#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_pkt_offset; int /*<<< orphan*/  max_pattern_len; int /*<<< orphan*/  min_pattern_len; int /*<<< orphan*/  max_patterns; } ;
struct nl80211_coalesce_rule_support {TYPE_1__ pat; int /*<<< orphan*/  max_delay; int /*<<< orphan*/  max_rules; } ;
struct TYPE_6__ {TYPE_2__* coalesce; } ;
struct cfg80211_registered_device {TYPE_3__ wiphy; } ;
typedef  int /*<<< orphan*/  rule ;
struct TYPE_5__ {int /*<<< orphan*/  max_pkt_offset; int /*<<< orphan*/  pattern_max_len; int /*<<< orphan*/  pattern_min_len; int /*<<< orphan*/  n_patterns; int /*<<< orphan*/  max_delay; int /*<<< orphan*/  n_rules; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  NL80211_ATTR_COALESCE_RULE ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct nl80211_coalesce_rule_support*) ; 

__attribute__((used)) static int nl80211_send_coalesce(struct sk_buff *msg,
				 struct cfg80211_registered_device *rdev)
{
	struct nl80211_coalesce_rule_support rule;

	if (!rdev->wiphy.coalesce)
		return 0;

	rule.max_rules = rdev->wiphy.coalesce->n_rules;
	rule.max_delay = rdev->wiphy.coalesce->max_delay;
	rule.pat.max_patterns = rdev->wiphy.coalesce->n_patterns;
	rule.pat.min_pattern_len = rdev->wiphy.coalesce->pattern_min_len;
	rule.pat.max_pattern_len = rdev->wiphy.coalesce->pattern_max_len;
	rule.pat.max_pkt_offset = rdev->wiphy.coalesce->max_pkt_offset;

	if (nla_put(msg, NL80211_ATTR_COALESCE_RULE, sizeof(rule), &rule))
		return -ENOBUFS;

	return 0;
}