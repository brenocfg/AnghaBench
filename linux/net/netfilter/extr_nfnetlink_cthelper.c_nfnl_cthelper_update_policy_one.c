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
struct nf_conntrack_expect_policy {scalar_t__ max_expected; void* timeout; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t NFCTH_POLICY_EXPECT_MAX ; 
 size_t NFCTH_POLICY_EXPECT_TIMEOUT ; 
 int /*<<< orphan*/  NFCTH_POLICY_MAX ; 
 size_t NFCTH_POLICY_NAME ; 
 scalar_t__ NF_CT_EXPECT_MAX_CNT ; 
 int /*<<< orphan*/  nfnl_cthelper_expect_pol ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nla_strcmp (struct nlattr*,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfnl_cthelper_update_policy_one(const struct nf_conntrack_expect_policy *policy,
				struct nf_conntrack_expect_policy *new_policy,
				const struct nlattr *attr)
{
	struct nlattr *tb[NFCTH_POLICY_MAX + 1];
	int err;

	err = nla_parse_nested_deprecated(tb, NFCTH_POLICY_MAX, attr,
					  nfnl_cthelper_expect_pol, NULL);
	if (err < 0)
		return err;

	if (!tb[NFCTH_POLICY_NAME] ||
	    !tb[NFCTH_POLICY_EXPECT_MAX] ||
	    !tb[NFCTH_POLICY_EXPECT_TIMEOUT])
		return -EINVAL;

	if (nla_strcmp(tb[NFCTH_POLICY_NAME], policy->name))
		return -EBUSY;

	new_policy->max_expected =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_MAX]));
	if (new_policy->max_expected > NF_CT_EXPECT_MAX_CNT)
		return -EINVAL;

	new_policy->timeout =
		ntohl(nla_get_be32(tb[NFCTH_POLICY_EXPECT_TIMEOUT]));

	return 0;
}