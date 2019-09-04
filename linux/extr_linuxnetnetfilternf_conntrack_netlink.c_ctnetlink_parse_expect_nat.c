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
typedef  int /*<<< orphan*/  u_int8_t ;
struct nlattr {int dummy; } ;
struct nf_conntrack_expect {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
ctnetlink_parse_expect_nat(const struct nlattr *attr,
			   struct nf_conntrack_expect *exp,
			   u_int8_t u3)
{
#ifdef CONFIG_NF_NAT_NEEDED
	struct nlattr *tb[CTA_EXPECT_NAT_MAX+1];
	struct nf_conntrack_tuple nat_tuple = {};
	int err;

	err = nla_parse_nested(tb, CTA_EXPECT_NAT_MAX, attr,
			       exp_nat_nla_policy, NULL);
	if (err < 0)
		return err;

	if (!tb[CTA_EXPECT_NAT_DIR] || !tb[CTA_EXPECT_NAT_TUPLE])
		return -EINVAL;

	err = ctnetlink_parse_tuple((const struct nlattr * const *)tb,
				    &nat_tuple, CTA_EXPECT_NAT_TUPLE,
				    u3, NULL);
	if (err < 0)
		return err;

	exp->saved_addr = nat_tuple.src.u3;
	exp->saved_proto = nat_tuple.src.u;
	exp->dir = ntohl(nla_get_be32(tb[CTA_EXPECT_NAT_DIR]));

	return 0;
#else
	return -EOPNOTSUPP;
#endif
}