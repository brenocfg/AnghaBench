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
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_v6_rcv_saddr; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_daddr; } ;
struct net {int dummy; } ;
struct inet_sock {scalar_t__ inet_dport; } ;
struct in6_addr {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {unsigned short udp_port_hash; } ;

/* Variables and functions */
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  inet6_mc_check (struct sock*,struct in6_addr const*,struct in6_addr const*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udp_sk_bound_dev_eq (struct net*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool __udp_v6_is_mcast_sock(struct net *net, struct sock *sk,
				   __be16 loc_port, const struct in6_addr *loc_addr,
				   __be16 rmt_port, const struct in6_addr *rmt_addr,
				   int dif, int sdif, unsigned short hnum)
{
	struct inet_sock *inet = inet_sk(sk);

	if (!net_eq(sock_net(sk), net))
		return false;

	if (udp_sk(sk)->udp_port_hash != hnum ||
	    sk->sk_family != PF_INET6 ||
	    (inet->inet_dport && inet->inet_dport != rmt_port) ||
	    (!ipv6_addr_any(&sk->sk_v6_daddr) &&
		    !ipv6_addr_equal(&sk->sk_v6_daddr, rmt_addr)) ||
	    !udp_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif) ||
	    (!ipv6_addr_any(&sk->sk_v6_rcv_saddr) &&
		    !ipv6_addr_equal(&sk->sk_v6_rcv_saddr, loc_addr)))
		return false;
	if (!inet6_mc_check(sk, loc_addr, rmt_addr))
		return false;
	return true;
}