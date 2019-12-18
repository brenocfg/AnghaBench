#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_2__ {int fib_has_custom_rules; int /*<<< orphan*/  fib_rules_require_fldissect; int /*<<< orphan*/  fib_num_tclassid_users; } ;
struct net {TYPE_1__ ipv4; } ;
struct fib_table {scalar_t__ tb_id; } ;
struct fib_rule_hdr {int tos; scalar_t__ dst_len; scalar_t__ src_len; } ;
struct fib_rule {scalar_t__ table; scalar_t__ action; int /*<<< orphan*/  l3mdev; } ;
struct fib4_rule {int tos; scalar_t__ dst_len; void* dstmask; scalar_t__ src_len; void* srcmask; scalar_t__ tclassid; void* dst; void* src; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 size_t FRA_DST ; 
 size_t FRA_FLOW ; 
 size_t FRA_SRC ; 
 scalar_t__ FR_ACT_TO_TBL ; 
 int IPTOS_TOS_MASK ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 scalar_t__ RT_TABLE_UNSPEC ; 
 struct fib_table* fib_empty_table (struct net*) ; 
 scalar_t__ fib_rule_requires_fldissect (struct fib_rule*) ; 
 int fib_unmerge (struct net*) ; 
 void* inet_make_mask (scalar_t__) ; 
 void* nla_get_in_addr (struct nlattr*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib4_rule_configure(struct fib_rule *rule, struct sk_buff *skb,
			       struct fib_rule_hdr *frh,
			       struct nlattr **tb,
			       struct netlink_ext_ack *extack)
{
	struct net *net = sock_net(skb->sk);
	int err = -EINVAL;
	struct fib4_rule *rule4 = (struct fib4_rule *) rule;

	if (frh->tos & ~IPTOS_TOS_MASK) {
		NL_SET_ERR_MSG(extack, "Invalid tos");
		goto errout;
	}

	/* split local/main if they are not already split */
	err = fib_unmerge(net);
	if (err)
		goto errout;

	if (rule->table == RT_TABLE_UNSPEC && !rule->l3mdev) {
		if (rule->action == FR_ACT_TO_TBL) {
			struct fib_table *table;

			table = fib_empty_table(net);
			if (!table) {
				err = -ENOBUFS;
				goto errout;
			}

			rule->table = table->tb_id;
		}
	}

	if (frh->src_len)
		rule4->src = nla_get_in_addr(tb[FRA_SRC]);

	if (frh->dst_len)
		rule4->dst = nla_get_in_addr(tb[FRA_DST]);

#ifdef CONFIG_IP_ROUTE_CLASSID
	if (tb[FRA_FLOW]) {
		rule4->tclassid = nla_get_u32(tb[FRA_FLOW]);
		if (rule4->tclassid)
			net->ipv4.fib_num_tclassid_users++;
	}
#endif

	if (fib_rule_requires_fldissect(rule))
		net->ipv4.fib_rules_require_fldissect++;

	rule4->src_len = frh->src_len;
	rule4->srcmask = inet_make_mask(rule4->src_len);
	rule4->dst_len = frh->dst_len;
	rule4->dstmask = inet_make_mask(rule4->dst_len);
	rule4->tos = frh->tos;

	net->ipv4.fib_has_custom_rules = true;

	err = 0;
errout:
	return err;
}