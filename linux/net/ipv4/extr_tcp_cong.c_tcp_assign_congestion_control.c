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
struct tcp_congestion_ops {int flags; int /*<<< orphan*/  owner; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_congestion_control; } ;
struct net {TYPE_1__ ipv4; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_ca_priv; struct tcp_congestion_ops const* icsk_ca_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_dontxmit (struct sock*) ; 
 int /*<<< orphan*/  INET_ECN_xmit (struct sock*) ; 
 int TCP_CONG_NEEDS_ECN ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tcp_congestion_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct net* sock_net (struct sock*) ; 
 struct tcp_congestion_ops tcp_reno ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void tcp_assign_congestion_control(struct sock *sk)
{
	struct net *net = sock_net(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	const struct tcp_congestion_ops *ca;

	rcu_read_lock();
	ca = rcu_dereference(net->ipv4.tcp_congestion_control);
	if (unlikely(!try_module_get(ca->owner)))
		ca = &tcp_reno;
	icsk->icsk_ca_ops = ca;
	rcu_read_unlock();

	memset(icsk->icsk_ca_priv, 0, sizeof(icsk->icsk_ca_priv));
	if (ca->flags & TCP_CONG_NEEDS_ECN)
		INET_ECN_xmit(sk);
	else
		INET_ECN_dontxmit(sk);
}