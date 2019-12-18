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
struct sock {int dummy; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int __ipv6_sock_mc_join (struct sock*,int,struct in6_addr const*,unsigned int) ; 

int ipv6_sock_mc_join_ssm(struct sock *sk, int ifindex,
			  const struct in6_addr *addr, unsigned int mode)
{
	return __ipv6_sock_mc_join(sk, ifindex, addr, mode);
}