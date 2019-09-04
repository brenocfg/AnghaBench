#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct TYPE_2__ {int /*<<< orphan*/  faddr; scalar_t__ srr; } ;
struct ip_options_rcu {TYPE_1__ opt; } ;
struct inet_sock {int /*<<< orphan*/  inet_saddr; scalar_t__ hdrincl; int /*<<< orphan*/  inet_opt; int /*<<< orphan*/  inet_daddr; } ;
struct flowi4 {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock const*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  flowi4_init_output (struct flowi4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  inet_sk_flowi_flags (struct sock const*) ; 
 struct ip_options_rcu* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void build_sk_flow_key(struct flowi4 *fl4, const struct sock *sk)
{
	const struct inet_sock *inet = inet_sk(sk);
	const struct ip_options_rcu *inet_opt;
	__be32 daddr = inet->inet_daddr;

	rcu_read_lock();
	inet_opt = rcu_dereference(inet->inet_opt);
	if (inet_opt && inet_opt->opt.srr)
		daddr = inet_opt->opt.faddr;
	flowi4_init_output(fl4, sk->sk_bound_dev_if, sk->sk_mark,
			   RT_CONN_FLAGS(sk), RT_SCOPE_UNIVERSE,
			   inet->hdrincl ? IPPROTO_RAW : sk->sk_protocol,
			   inet_sk_flowi_flags(sk),
			   daddr, inet->inet_saddr, 0, 0, sk->sk_uid);
	rcu_read_unlock();
}