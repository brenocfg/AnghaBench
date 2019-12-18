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

/* Variables and functions */
 int /*<<< orphan*/  NLMSG_ALIGN (int /*<<< orphan*/ ) ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 int /*<<< orphan*/  TCA_ACT_MAX_PRIO ; 
 size_t TCA_ACT_TAB ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 scalar_t__ nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_action_policy ; 

__attribute__((used)) static struct nlattr *find_dump_kind(struct nlattr **nla)
{
	struct nlattr *tb1, *tb2[TCA_ACT_MAX + 1];
	struct nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	struct nlattr *kind;

	tb1 = nla[TCA_ACT_TAB];
	if (tb1 == NULL)
		return NULL;

	if (nla_parse_deprecated(tb, TCA_ACT_MAX_PRIO, nla_data(tb1), NLMSG_ALIGN(nla_len(tb1)), NULL, NULL) < 0)
		return NULL;

	if (tb[1] == NULL)
		return NULL;
	if (nla_parse_nested_deprecated(tb2, TCA_ACT_MAX, tb[1], tcf_action_policy, NULL) < 0)
		return NULL;
	kind = tb2[TCA_ACT_KIND];

	return kind;
}