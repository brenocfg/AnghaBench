#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_state; int sk_userlocks; int sk_err_soft; scalar_t__ sk_route_caps; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_protocol; } ;
struct rtable {int /*<<< orphan*/  dst; } ;
struct TYPE_8__ {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct flowi4 {int dummy; } ;
struct TYPE_9__ {struct flowi4 ip4; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
struct TYPE_11__ {TYPE_3__ fl; } ;
struct inet_sock {int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_saddr; TYPE_4__ cork; int /*<<< orphan*/  inet_daddr; int /*<<< orphan*/  inet_opt; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_12__ {int /*<<< orphan*/  sysctl_ip_dynaddr; } ;
struct TYPE_13__ {TYPE_5__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock*) ; 
 int SOCK_BINDADDR_LOCK ; 
 scalar_t__ TCP_SYN_SENT ; 
 scalar_t__ __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int inet_sk_reselect_saddr (struct sock*) ; 
 struct rtable* ip_route_output_ports (TYPE_6__*,struct flowi4*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,int /*<<< orphan*/ *) ; 
 TYPE_6__* sock_net (struct sock*) ; 

int inet_sk_rebuild_header(struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct rtable *rt = (struct rtable *)__sk_dst_check(sk, 0);
	__be32 daddr;
	struct ip_options_rcu *inet_opt;
	struct flowi4 *fl4;
	int err;

	/* Route is OK, nothing to do. */
	if (rt)
		return 0;

	/* Reroute. */
	rcu_read_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	daddr = inet->inet_daddr;
	if (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	rcu_read_unlock();
	fl4 = &inet->cork.fl.u.ip4;
	rt = ip_route_output_ports(sock_net(sk), fl4, sk, daddr, inet->inet_saddr,
				   inet->inet_dport, inet->inet_sport,
				   sk->sk_protocol, RT_CONN_FLAGS(sk),
				   sk->sk_bound_dev_if);
	if (!IS_ERR(rt)) {
		err = 0;
		sk_setup_caps(sk, &rt->dst);
	} else {
		err = PTR_ERR(rt);

		/* Routing failed... */
		sk->sk_route_caps = 0;
		/*
		 * Other protocols have to map its equivalent state to TCP_SYN_SENT.
		 * DCCP maps its DCCP_REQUESTING state to TCP_SYN_SENT. -acme
		 */
		if (!sock_net(sk)->ipv4.sysctl_ip_dynaddr ||
		    sk->sk_state != TCP_SYN_SENT ||
		    (sk->sk_userlocks & SOCK_BINDADDR_LOCK) ||
		    (err = inet_sk_reselect_saddr(sk)) != 0)
			sk->sk_err_soft = -err;
	}

	return err;
}