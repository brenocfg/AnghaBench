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
struct ipv6_pinfo {int /*<<< orphan*/  ipv6_mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipv6_sock_mc_close (struct sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void ipv6_sock_mc_close(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);

	if (!rcu_access_pointer(np->ipv6_mc_list))
		return;
	rtnl_lock();
	__ipv6_sock_mc_close(sk);
	rtnl_unlock();
}