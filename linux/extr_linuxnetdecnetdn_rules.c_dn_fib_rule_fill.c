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
struct fib_rule_hdr {scalar_t__ tos; scalar_t__ src_len; scalar_t__ dst_len; } ;
struct fib_rule {int dummy; } ;
struct dn_fib_rule {int /*<<< orphan*/  src; scalar_t__ src_len; int /*<<< orphan*/  dst; scalar_t__ dst_len; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  FRA_DST ; 
 int /*<<< orphan*/  FRA_SRC ; 
 scalar_t__ nla_put_le16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_fib_rule_fill(struct fib_rule *rule, struct sk_buff *skb,
			    struct fib_rule_hdr *frh)
{
	struct dn_fib_rule *r = (struct dn_fib_rule *)rule;

	frh->dst_len = r->dst_len;
	frh->src_len = r->src_len;
	frh->tos = 0;

	if ((r->dst_len &&
	     nla_put_le16(skb, FRA_DST, r->dst)) ||
	    (r->src_len &&
	     nla_put_le16(skb, FRA_SRC, r->src)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -ENOBUFS;
}