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
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ipv6_sock_mc_drop (struct sock*,int,struct in6_addr const*) ; 
 int ipv6_sock_mc_join (struct sock*,int,struct in6_addr const*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int ipv6_mc_config(struct sock *sk, bool join,
			  const struct in6_addr *addr, int ifindex)
{
	int ret;

	ASSERT_RTNL();

	lock_sock(sk);
	if (join)
		ret = ipv6_sock_mc_join(sk, ifindex, addr);
	else
		ret = ipv6_sock_mc_drop(sk, ifindex, addr);
	release_sock(sk);

	return ret;
}