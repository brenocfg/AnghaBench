#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ imr_multiaddr; int /*<<< orphan*/  imr_ifindex; } ;
struct ip_mc_socklist {TYPE_2__ multi; scalar_t__ next_rcu; } ;
struct inet_sock {scalar_t__ mc_list; } ;
struct in_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 struct in_device* inetdev_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_mc_dec_group (struct in_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_mc_leave_src (struct sock*,struct ip_mc_socklist*,struct in_device*) ; 
 int /*<<< orphan*/  kfree_rcu (struct ip_mc_socklist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct ip_mc_socklist* rtnl_dereference (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (struct sock*) ; 

void ip_mc_drop_socket(struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ip_mc_socklist *iml;
	struct net *net = sock_net(sk);

	if (!inet->mc_list)
		return;

	rtnl_lock();
	while ((iml = rtnl_dereference(inet->mc_list)) != NULL) {
		struct in_device *in_dev;

		inet->mc_list = iml->next_rcu;
		in_dev = inetdev_by_index(net, iml->multi.imr_ifindex);
		(void) ip_mc_leave_src(sk, iml, in_dev);
		if (in_dev)
			ip_mc_dec_group(in_dev, iml->multi.imr_multiaddr.s_addr);
		/* decrease mem now to avoid the memleak warning */
		atomic_sub(sizeof(*iml), &sk->sk_omem_alloc);
		kfree_rcu(iml, rcu);
	}
	rtnl_unlock();
}