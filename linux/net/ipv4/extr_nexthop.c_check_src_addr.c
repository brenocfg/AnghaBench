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
struct netlink_ext_ack {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr const*) ; 

__attribute__((used)) static int check_src_addr(const struct in6_addr *saddr,
			  struct netlink_ext_ack *extack)
{
	if (!ipv6_addr_any(saddr)) {
		NL_SET_ERR_MSG(extack, "IPv6 routes using source address can not use nexthop objects");
		return -EINVAL;
	}
	return 0;
}