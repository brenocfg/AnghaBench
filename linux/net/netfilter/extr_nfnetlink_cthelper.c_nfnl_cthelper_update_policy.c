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
struct nf_conntrack_helper {int expect_class_max; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  NFCTH_POLICY_SET_MAX ; 
 size_t NFCTH_POLICY_SET_NUM ; 
 int /*<<< orphan*/  nfnl_cthelper_expect_policy_set ; 
 int nfnl_cthelper_update_policy_all (struct nlattr**,struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfnl_cthelper_update_policy(struct nf_conntrack_helper *helper,
				       const struct nlattr *attr)
{
	struct nlattr *tb[NFCTH_POLICY_SET_MAX + 1];
	unsigned int class_max;
	int err;

	err = nla_parse_nested_deprecated(tb, NFCTH_POLICY_SET_MAX, attr,
					  nfnl_cthelper_expect_policy_set,
					  NULL);
	if (err < 0)
		return err;

	if (!tb[NFCTH_POLICY_SET_NUM])
		return -EINVAL;

	class_max = ntohl(nla_get_be32(tb[NFCTH_POLICY_SET_NUM]));
	if (helper->expect_class_max + 1 != class_max)
		return -EBUSY;

	return nfnl_cthelper_update_policy_all(tb, helper);
}