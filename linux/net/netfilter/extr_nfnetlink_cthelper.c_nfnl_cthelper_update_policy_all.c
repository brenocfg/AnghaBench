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
struct nf_conntrack_helper {int expect_class_max; int /*<<< orphan*/ * expect_policy; } ;
struct nf_conntrack_expect_policy {int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_expected; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFCTH_POLICY_SET ; 
 int /*<<< orphan*/  kfree (struct nf_conntrack_expect_policy*) ; 
 struct nf_conntrack_expect_policy* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int nfnl_cthelper_update_policy_one (int /*<<< orphan*/ *,struct nf_conntrack_expect_policy*,struct nlattr*) ; 

__attribute__((used)) static int nfnl_cthelper_update_policy_all(struct nlattr *tb[],
					   struct nf_conntrack_helper *helper)
{
	struct nf_conntrack_expect_policy *new_policy;
	struct nf_conntrack_expect_policy *policy;
	int i, ret = 0;

	new_policy = kmalloc_array(helper->expect_class_max + 1,
				   sizeof(*new_policy), GFP_KERNEL);
	if (!new_policy)
		return -ENOMEM;

	/* Check first that all policy attributes are well-formed, so we don't
	 * leave things in inconsistent state on errors.
	 */
	for (i = 0; i < helper->expect_class_max + 1; i++) {

		if (!tb[NFCTH_POLICY_SET + i]) {
			ret = -EINVAL;
			goto err;
		}

		ret = nfnl_cthelper_update_policy_one(&helper->expect_policy[i],
						      &new_policy[i],
						      tb[NFCTH_POLICY_SET + i]);
		if (ret < 0)
			goto err;
	}
	/* Now we can safely update them. */
	for (i = 0; i < helper->expect_class_max + 1; i++) {
		policy = (struct nf_conntrack_expect_policy *)
				&helper->expect_policy[i];
		policy->max_expected = new_policy->max_expected;
		policy->timeout	= new_policy->timeout;
	}

err:
	kfree(new_policy);
	return ret;
}