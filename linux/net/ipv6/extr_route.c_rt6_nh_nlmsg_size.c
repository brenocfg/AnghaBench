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
struct rtnexthop {int dummy; } ;
struct fib6_nh {scalar_t__ fib_nh_lws; } ;

/* Variables and functions */
 scalar_t__ NLA_ALIGN (int) ; 
 scalar_t__ lwtunnel_get_encap_size (scalar_t__) ; 
 scalar_t__ nla_total_size (int) ; 

__attribute__((used)) static int rt6_nh_nlmsg_size(struct fib6_nh *nh, void *arg)
{
	int *nexthop_len = arg;

	*nexthop_len += nla_total_size(0)	 /* RTA_MULTIPATH */
		     + NLA_ALIGN(sizeof(struct rtnexthop))
		     + nla_total_size(16); /* RTA_GATEWAY */

	if (nh->fib_nh_lws) {
		/* RTA_ENCAP_TYPE */
		*nexthop_len += lwtunnel_get_encap_size(nh->fib_nh_lws);
		/* RTA_ENCAP */
		*nexthop_len += nla_total_size(2);
	}

	return 0;
}