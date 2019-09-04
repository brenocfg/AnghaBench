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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nlattr {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 size_t IPSET_ATTR_IPADDR_IPV6 ; 
 int /*<<< orphan*/  IPSET_ATTR_IPADDR_MAX ; 
 int IPSET_ERR_PROTOCOL ; 
 int /*<<< orphan*/  flag_nested (struct nlattr*) ; 
 int /*<<< orphan*/  ip_set_attr_netorder (struct nlattr**,size_t) ; 
 int /*<<< orphan*/  ipaddr_policy ; 
 int /*<<< orphan*/  memcpy (union nf_inet_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int
ip_set_get_ipaddr6(struct nlattr *nla, union nf_inet_addr *ipaddr)
{
	struct nlattr *tb[IPSET_ATTR_IPADDR_MAX + 1];

	if (unlikely(!flag_nested(nla)))
		return -IPSET_ERR_PROTOCOL;

	if (nla_parse_nested(tb, IPSET_ATTR_IPADDR_MAX, nla,
			     ipaddr_policy, NULL))
		return -IPSET_ERR_PROTOCOL;
	if (unlikely(!ip_set_attr_netorder(tb, IPSET_ATTR_IPADDR_IPV6)))
		return -IPSET_ERR_PROTOCOL;

	memcpy(ipaddr, nla_data(tb[IPSET_ATTR_IPADDR_IPV6]),
	       sizeof(struct in6_addr));
	return 0;
}