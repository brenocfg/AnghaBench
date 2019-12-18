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
struct sk_buff {int dummy; } ;
struct fib_rule_hdr {int /*<<< orphan*/  tos; scalar_t__ src_len; scalar_t__ dst_len; } ;
struct fib_rule {int dummy; } ;
struct fib4_rule {scalar_t__ tclassid; int /*<<< orphan*/  src; scalar_t__ src_len; int /*<<< orphan*/  dst; scalar_t__ dst_len; int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  FRA_DST ; 
 int /*<<< orphan*/  FRA_FLOW ; 
 int /*<<< orphan*/  FRA_SRC ; 
 scalar_t__ nla_put_in_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fib4_rule_fill(struct fib_rule *rule, struct sk_buff *skb,
			  struct fib_rule_hdr *frh)
{
	struct fib4_rule *rule4 = (struct fib4_rule *) rule;

	frh->dst_len = rule4->dst_len;
	frh->src_len = rule4->src_len;
	frh->tos = rule4->tos;

	if ((rule4->dst_len &&
	     nla_put_in_addr(skb, FRA_DST, rule4->dst)) ||
	    (rule4->src_len &&
	     nla_put_in_addr(skb, FRA_SRC, rule4->src)))
		goto nla_put_failure;
#ifdef CONFIG_IP_ROUTE_CLASSID
	if (rule4->tclassid &&
	    nla_put_u32(skb, FRA_FLOW, rule4->tclassid))
		goto nla_put_failure;
#endif
	return 0;

nla_put_failure:
	return -ENOBUFS;
}