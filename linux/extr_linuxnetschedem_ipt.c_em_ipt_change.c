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
struct xt_match {int /*<<< orphan*/  me; } ;
struct tcf_ematch {int datalen; unsigned long data; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
struct em_ipt_match {int /*<<< orphan*/  match_data; int /*<<< orphan*/  hook; struct xt_match* match; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct xt_match*) ; 
 int PTR_ERR (struct xt_match*) ; 
 size_t TCA_EM_IPT_HOOK ; 
 size_t TCA_EM_IPT_MATCH_DATA ; 
 size_t TCA_EM_IPT_MATCH_NAME ; 
 int /*<<< orphan*/  TCA_EM_IPT_MAX ; 
 size_t TCA_EM_IPT_NFPROTO ; 
 int XT_ALIGN (int /*<<< orphan*/ ) ; 
 int check_match (struct net*,struct em_ipt_match*,int) ; 
 int /*<<< orphan*/  em_ipt_policy ; 
 struct xt_match* get_xt_match (struct nlattr**) ; 
 int /*<<< orphan*/  kfree (struct em_ipt_match*) ; 
 struct em_ipt_match* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,struct nlattr*,int) ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int em_ipt_change(struct net *net, void *data, int data_len,
			 struct tcf_ematch *em)
{
	struct nlattr *tb[TCA_EM_IPT_MAX + 1];
	struct em_ipt_match *im = NULL;
	struct xt_match *match;
	int mdata_len, ret;

	ret = nla_parse(tb, TCA_EM_IPT_MAX, data, data_len, em_ipt_policy,
			NULL);
	if (ret < 0)
		return ret;

	if (!tb[TCA_EM_IPT_HOOK] || !tb[TCA_EM_IPT_MATCH_NAME] ||
	    !tb[TCA_EM_IPT_MATCH_DATA] || !tb[TCA_EM_IPT_NFPROTO])
		return -EINVAL;

	match = get_xt_match(tb);
	if (IS_ERR(match)) {
		pr_err("unable to load match\n");
		return PTR_ERR(match);
	}

	mdata_len = XT_ALIGN(nla_len(tb[TCA_EM_IPT_MATCH_DATA]));
	im = kzalloc(sizeof(*im) + mdata_len, GFP_KERNEL);
	if (!im) {
		ret = -ENOMEM;
		goto err;
	}

	im->match = match;
	im->hook = nla_get_u32(tb[TCA_EM_IPT_HOOK]);
	nla_memcpy(im->match_data, tb[TCA_EM_IPT_MATCH_DATA], mdata_len);

	ret = check_match(net, im, mdata_len);
	if (ret)
		goto err;

	em->datalen = sizeof(*im) + mdata_len;
	em->data = (unsigned long)im;
	return 0;

err:
	kfree(im);
	module_put(match->me);
	return ret;
}