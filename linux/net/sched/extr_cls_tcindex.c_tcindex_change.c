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
typedef  int /*<<< orphan*/  u32 ;
struct tcindex_filter_result {int dummy; } ;
struct tcindex_data {int dummy; } ;
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  TCA_TCINDEX_MAX ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct tcf_proto*,int /*<<< orphan*/ ,struct nlattr**,void**,struct nlattr*,struct tcindex_data*,struct tcindex_filter_result*,void*) ; 
 struct tcindex_data* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcindex_policy ; 
 int tcindex_set_parms (struct net*,struct tcf_proto*,unsigned long,int /*<<< orphan*/ ,struct tcindex_data*,struct tcindex_filter_result*,struct nlattr**,struct nlattr*,int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int
tcindex_change(struct net *net, struct sk_buff *in_skb,
	       struct tcf_proto *tp, unsigned long base, u32 handle,
	       struct nlattr **tca, void **arg, bool ovr,
	       bool rtnl_held, struct netlink_ext_ack *extack)
{
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_TCINDEX_MAX + 1];
	struct tcindex_data *p = rtnl_dereference(tp->root);
	struct tcindex_filter_result *r = *arg;
	int err;

	pr_debug("tcindex_change(tp %p,handle 0x%08x,tca %p,arg %p),opt %p,"
	    "p %p,r %p,*arg %p\n",
	    tp, handle, tca, arg, opt, p, r, arg ? *arg : NULL);

	if (!opt)
		return 0;

	err = nla_parse_nested_deprecated(tb, TCA_TCINDEX_MAX, opt,
					  tcindex_policy, NULL);
	if (err < 0)
		return err;

	return tcindex_set_parms(net, tp, base, handle, p, r, tb,
				 tca[TCA_RATE], ovr, extack);
}