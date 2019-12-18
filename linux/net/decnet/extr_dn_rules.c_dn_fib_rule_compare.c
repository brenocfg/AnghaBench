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
struct fib_rule_hdr {scalar_t__ src_len; scalar_t__ dst_len; } ;
struct fib_rule {int dummy; } ;
struct dn_fib_rule {scalar_t__ src_len; scalar_t__ dst_len; scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 size_t FRA_DST ; 
 size_t FRA_SRC ; 
 scalar_t__ nla_get_le16 (struct nlattr*) ; 

__attribute__((used)) static int dn_fib_rule_compare(struct fib_rule *rule, struct fib_rule_hdr *frh,
			       struct nlattr **tb)
{
	struct dn_fib_rule *r = (struct dn_fib_rule *)rule;

	if (frh->src_len && (r->src_len != frh->src_len))
		return 0;

	if (frh->dst_len && (r->dst_len != frh->dst_len))
		return 0;

	if (frh->src_len && (r->src != nla_get_le16(tb[FRA_SRC])))
		return 0;

	if (frh->dst_len && (r->dst != nla_get_le16(tb[FRA_DST])))
		return 0;

	return 1;
}