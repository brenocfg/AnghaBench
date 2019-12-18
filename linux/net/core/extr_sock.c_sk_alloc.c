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
struct sock {int sk_family; int sk_kern_sock; int sk_net_refcnt; int /*<<< orphan*/  sk_cgrp_data; int /*<<< orphan*/  sk_wmem_alloc; struct proto* sk_prot_creator; struct proto* sk_prot; } ;
struct proto {int dummy; } ;
struct net {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 int /*<<< orphan*/  cgroup_sk_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mem_cgroup_sk_alloc (struct sock*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 struct sock* sk_prot_alloc (struct proto*,int,int) ; 
 int /*<<< orphan*/  sock_inuse_add (struct net*,int) ; 
 int /*<<< orphan*/  sock_lock_init (struct sock*) ; 
 int /*<<< orphan*/  sock_net_set (struct sock*,struct net*) ; 
 int /*<<< orphan*/  sock_update_classid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_update_netprioidx (int /*<<< orphan*/ *) ; 

struct sock *sk_alloc(struct net *net, int family, gfp_t priority,
		      struct proto *prot, int kern)
{
	struct sock *sk;

	sk = sk_prot_alloc(prot, priority | __GFP_ZERO, family);
	if (sk) {
		sk->sk_family = family;
		/*
		 * See comment in struct sock definition to understand
		 * why we need sk_prot_creator -acme
		 */
		sk->sk_prot = sk->sk_prot_creator = prot;
		sk->sk_kern_sock = kern;
		sock_lock_init(sk);
		sk->sk_net_refcnt = kern ? 0 : 1;
		if (likely(sk->sk_net_refcnt)) {
			get_net(net);
			sock_inuse_add(net, 1);
		}

		sock_net_set(sk, net);
		refcount_set(&sk->sk_wmem_alloc, 1);

		mem_cgroup_sk_alloc(sk);
		cgroup_sk_alloc(&sk->sk_cgrp_data);
		sock_update_classid(&sk->sk_cgrp_data);
		sock_update_netprioidx(&sk->sk_cgrp_data);
	}

	return sk;
}