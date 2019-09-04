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
struct inetpeer_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
struct genl_info {struct nlattr** attrs; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  inetpeer_get_addr_v4 (struct inetpeer_addr*) ; 
 int /*<<< orphan*/  inetpeer_get_addr_v6 (struct inetpeer_addr*) ; 
 int /*<<< orphan*/  inetpeer_set_addr_v4 (struct inetpeer_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetpeer_set_addr_v6 (struct inetpeer_addr*,struct in6_addr*) ; 
 unsigned int ipv4_addr_hash (int /*<<< orphan*/ ) ; 
 unsigned int ipv6_addr_hash (int /*<<< orphan*/ ) ; 
 struct in6_addr nla_get_in6_addr (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_in_addr (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 

__attribute__((used)) static int __parse_nl_addr(struct genl_info *info, struct inetpeer_addr *addr,
			   unsigned int *hash, int optional, int v4, int v6)
{
	struct nlattr *a;

	a = info->attrs[v4];
	if (a) {
		inetpeer_set_addr_v4(addr, nla_get_in_addr(a));
		if (hash)
			*hash = ipv4_addr_hash(inetpeer_get_addr_v4(addr));
		return 0;
	}
	a = info->attrs[v6];
	if (a) {
		struct in6_addr in6;

		if (nla_len(a) != sizeof(struct in6_addr))
			return -EINVAL;
		in6 = nla_get_in6_addr(a);
		inetpeer_set_addr_v6(addr, &in6);
		if (hash)
			*hash = ipv6_addr_hash(inetpeer_get_addr_v6(addr));
		return 0;
	}
	return optional ? 1 : -EAFNOSUPPORT;
}