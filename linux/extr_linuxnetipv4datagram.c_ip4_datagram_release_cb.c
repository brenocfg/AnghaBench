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
struct sock {int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_protocol; } ;
struct dst_entry {TYPE_1__* ops; int /*<<< orphan*/  obsolete; } ;
struct rtable {struct dst_entry dst; } ;
struct TYPE_4__ {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_2__ opt; } ;
struct inet_sock {int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_saddr; int /*<<< orphan*/  inet_opt; int /*<<< orphan*/  inet_daddr; } ;
struct flowi4 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {scalar_t__ (* check ) (struct dst_entry*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock*) ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 struct rtable* ip_route_output_ports (int /*<<< orphan*/ ,struct flowi4*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_dst_set (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ stub1 (struct dst_entry*,int /*<<< orphan*/ ) ; 

void ip4_datagram_release_cb(struct sock *sk)
{
	const struct inet_sock *inet = inet_sk(sk);
	const struct ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;
	struct dst_entry *dst;
	struct flowi4 fl4;
	struct rtable *rt;

	rcu_read_lock();

	dst = __sk_dst_get(sk);
	if (!dst || !dst->obsolete || dst->ops->check(dst, 0)) {
		rcu_read_unlock();
		return;
	}
	inet_opt = rcu_dereference(inet->inet_opt);
	if (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	rt = ip_route_output_ports(sock_net(sk), &fl4, sk, daddr,
				   inet->inet_saddr, inet->inet_dport,
				   inet->inet_sport, sk->sk_protocol,
				   RT_CONN_FLAGS(sk), sk->sk_bound_dev_if);

	dst = !IS_ERR(rt) ? &rt->dst : NULL;
	sk_dst_set(sk, dst);

	rcu_read_unlock();
}