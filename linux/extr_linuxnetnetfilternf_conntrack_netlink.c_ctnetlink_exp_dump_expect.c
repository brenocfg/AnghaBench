#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_ct_helper_expectfn {int /*<<< orphan*/  name; } ;
struct nf_conntrack_helper {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct nf_conntrack_expect {unsigned long flags; unsigned long class; int /*<<< orphan*/  expectfn; int /*<<< orphan*/  mask; int /*<<< orphan*/  tuple; TYPE_1__ timeout; struct nf_conn* master; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {TYPE_2__* tuplehash; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_EXPECT_CLASS ; 
 int /*<<< orphan*/  CTA_EXPECT_FLAGS ; 
 int /*<<< orphan*/  CTA_EXPECT_FN ; 
 int /*<<< orphan*/  CTA_EXPECT_HELP_NAME ; 
 int /*<<< orphan*/  CTA_EXPECT_ID ; 
 int /*<<< orphan*/  CTA_EXPECT_MASTER ; 
 int /*<<< orphan*/  CTA_EXPECT_TIMEOUT ; 
 int /*<<< orphan*/  CTA_EXPECT_TUPLE ; 
 long HZ ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 scalar_t__ ctnetlink_exp_dump_mask (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ctnetlink_exp_dump_tuple (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 
 scalar_t__ jiffies ; 
 struct nf_ct_helper_expectfn* nf_ct_helper_expectfn_find_by_symbol (int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conntrack_helper* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctnetlink_exp_dump_expect(struct sk_buff *skb,
			  const struct nf_conntrack_expect *exp)
{
	struct nf_conn *master = exp->master;
	long timeout = ((long)exp->timeout.expires - (long)jiffies) / HZ;
	struct nf_conn_help *help;
#ifdef CONFIG_NF_NAT_NEEDED
	struct nlattr *nest_parms;
	struct nf_conntrack_tuple nat_tuple = {};
#endif
	struct nf_ct_helper_expectfn *expfn;

	if (timeout < 0)
		timeout = 0;

	if (ctnetlink_exp_dump_tuple(skb, &exp->tuple, CTA_EXPECT_TUPLE) < 0)
		goto nla_put_failure;
	if (ctnetlink_exp_dump_mask(skb, &exp->tuple, &exp->mask) < 0)
		goto nla_put_failure;
	if (ctnetlink_exp_dump_tuple(skb,
				 &master->tuplehash[IP_CT_DIR_ORIGINAL].tuple,
				 CTA_EXPECT_MASTER) < 0)
		goto nla_put_failure;

#ifdef CONFIG_NF_NAT_NEEDED
	if (!nf_inet_addr_cmp(&exp->saved_addr, &any_addr) ||
	    exp->saved_proto.all) {
		nest_parms = nla_nest_start(skb, CTA_EXPECT_NAT | NLA_F_NESTED);
		if (!nest_parms)
			goto nla_put_failure;

		if (nla_put_be32(skb, CTA_EXPECT_NAT_DIR, htonl(exp->dir)))
			goto nla_put_failure;

		nat_tuple.src.l3num = nf_ct_l3num(master);
		nat_tuple.src.u3 = exp->saved_addr;
		nat_tuple.dst.protonum = nf_ct_protonum(master);
		nat_tuple.src.u = exp->saved_proto;

		if (ctnetlink_exp_dump_tuple(skb, &nat_tuple,
						CTA_EXPECT_NAT_TUPLE) < 0)
	                goto nla_put_failure;
	        nla_nest_end(skb, nest_parms);
	}
#endif
	if (nla_put_be32(skb, CTA_EXPECT_TIMEOUT, htonl(timeout)) ||
	    nla_put_be32(skb, CTA_EXPECT_ID, htonl((unsigned long)exp)) ||
	    nla_put_be32(skb, CTA_EXPECT_FLAGS, htonl(exp->flags)) ||
	    nla_put_be32(skb, CTA_EXPECT_CLASS, htonl(exp->class)))
		goto nla_put_failure;
	help = nfct_help(master);
	if (help) {
		struct nf_conntrack_helper *helper;

		helper = rcu_dereference(help->helper);
		if (helper &&
		    nla_put_string(skb, CTA_EXPECT_HELP_NAME, helper->name))
			goto nla_put_failure;
	}
	expfn = nf_ct_helper_expectfn_find_by_symbol(exp->expectfn);
	if (expfn != NULL &&
	    nla_put_string(skb, CTA_EXPECT_FN, expfn->name))
		goto nla_put_failure;

	return 0;

nla_put_failure:
	return -1;
}