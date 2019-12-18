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
struct nf_conntrack_helper {unsigned int expect_class_max; struct nf_conntrack_expect_policy* expect_policy; } ;
struct nf_conntrack_expect_policy {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFCTH_POLICY_SET ; 
 int /*<<< orphan*/  NFCTH_POLICY_SET_MAX ; 
 size_t NFCTH_POLICY_SET_NUM ; 
 unsigned int NF_CT_MAX_EXPECT_CLASSES ; 
 struct nf_conntrack_expect_policy* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nf_conntrack_expect_policy*) ; 
 int nfnl_cthelper_expect_policy (struct nf_conntrack_expect_policy*,struct nlattr*) ; 
 int /*<<< orphan*/  nfnl_cthelper_expect_policy_set ; 
 int /*<<< orphan*/  nla_get_be32 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfnl_cthelper_parse_expect_policy(struct nf_conntrack_helper *helper,
				  const struct nlattr *attr)
{
	int i, ret;
	struct nf_conntrack_expect_policy *expect_policy;
	struct nlattr *tb[NFCTH_POLICY_SET_MAX+1];
	unsigned int class_max;

	ret = nla_parse_nested_deprecated(tb, NFCTH_POLICY_SET_MAX, attr,
					  nfnl_cthelper_expect_policy_set,
					  NULL);
	if (ret < 0)
		return ret;

	if (!tb[NFCTH_POLICY_SET_NUM])
		return -EINVAL;

	class_max = ntohl(nla_get_be32(tb[NFCTH_POLICY_SET_NUM]));
	if (class_max == 0)
		return -EINVAL;
	if (class_max > NF_CT_MAX_EXPECT_CLASSES)
		return -EOVERFLOW;

	expect_policy = kcalloc(class_max,
				sizeof(struct nf_conntrack_expect_policy),
				GFP_KERNEL);
	if (expect_policy == NULL)
		return -ENOMEM;

	for (i = 0; i < class_max; i++) {
		if (!tb[NFCTH_POLICY_SET+i])
			goto err;

		ret = nfnl_cthelper_expect_policy(&expect_policy[i],
						  tb[NFCTH_POLICY_SET+i]);
		if (ret < 0)
			goto err;
	}

	helper->expect_class_max = class_max - 1;
	helper->expect_policy = expect_policy;
	return 0;
err:
	kfree(expect_policy);
	return -EINVAL;
}