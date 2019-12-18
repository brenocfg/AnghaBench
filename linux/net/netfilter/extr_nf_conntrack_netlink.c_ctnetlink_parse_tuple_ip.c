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
struct nlattr {int dummy; } ;
struct TYPE_2__ {int l3num; } ;
struct nf_conntrack_tuple {TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_IP_MAX ; 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  cta_ip_nla_policy ; 
 int ipv4_nlattr_to_tuple (struct nlattr**,struct nf_conntrack_tuple*) ; 
 int ipv6_nlattr_to_tuple (struct nlattr**,struct nf_conntrack_tuple*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nla_validate_nested_deprecated (struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ctnetlink_parse_tuple_ip(struct nlattr *attr,
				    struct nf_conntrack_tuple *tuple)
{
	struct nlattr *tb[CTA_IP_MAX+1];
	int ret = 0;

	ret = nla_parse_nested_deprecated(tb, CTA_IP_MAX, attr, NULL, NULL);
	if (ret < 0)
		return ret;

	ret = nla_validate_nested_deprecated(attr, CTA_IP_MAX,
					     cta_ip_nla_policy, NULL);
	if (ret)
		return ret;

	switch (tuple->src.l3num) {
	case NFPROTO_IPV4:
		ret = ipv4_nlattr_to_tuple(tb, tuple);
		break;
	case NFPROTO_IPV6:
		ret = ipv6_nlattr_to_tuple(tb, tuple);
		break;
	}

	return ret;
}