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
struct fib_rule_hdr {int /*<<< orphan*/  tos; scalar_t__ src_len; scalar_t__ dst_len; } ;
struct fib_rule {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ plen; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; scalar_t__ plen; } ;
struct fib6_rule {TYPE_1__ src; TYPE_2__ dst; int /*<<< orphan*/  tclass; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  FRA_DST ; 
 int /*<<< orphan*/  FRA_SRC ; 
 scalar_t__ nla_put_in6_addr (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_rule_fill(struct fib_rule *rule, struct sk_buff *skb,
			  struct fib_rule_hdr *frh)
{
	struct fib6_rule *rule6 = (struct fib6_rule *) rule;

	frh->dst_len = rule6->dst.plen;
	frh->src_len = rule6->src.plen;
	frh->tos = rule6->tclass;

	if ((rule6->dst.plen &&
	     nla_put_in6_addr(skb, FRA_DST, &rule6->dst.addr)) ||
	    (rule6->src.plen &&
	     nla_put_in6_addr(skb, FRA_SRC, &rule6->src.addr)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -ENOBUFS;
}