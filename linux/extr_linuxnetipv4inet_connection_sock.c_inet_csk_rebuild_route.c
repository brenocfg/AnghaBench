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
struct dst_entry {int dummy; } ;
struct rtable {struct dst_entry dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct inet_sock {int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_saddr; int /*<<< orphan*/  inet_opt; int /*<<< orphan*/  inet_daddr; } ;
struct flowi4 {int dummy; } ;
struct TYPE_4__ {struct flowi4 ip4; } ;
struct flowi {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 struct rtable* ip_route_output_ports (int /*<<< orphan*/ ,struct flowi4*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static struct dst_entry *inet_csk_rebuild_route(struct sock *sk, struct flowi *fl)
{
	const struct inet_sock *inet = inet_sk(sk);
	const struct ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;
	struct flowi4 *fl4;
	struct rtable *rt;

	rcu_read_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	if (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	fl4 = &fl->u.ip4;
	rt = ip_route_output_ports(sock_net(sk), fl4, sk, daddr,
				   inet->inet_saddr, inet->inet_dport,
				   inet->inet_sport, sk->sk_protocol,
				   RT_CONN_FLAGS(sk), sk->sk_bound_dev_if);
	if (IS_ERR(rt))
		rt = NULL;
	if (rt)
		sk_setup_caps(sk, &rt->dst);
	rcu_read_unlock();

	return &rt->dst;
}