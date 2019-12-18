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
struct sock {scalar_t__ sk_family; int /*<<< orphan*/  sk_incoming_cpu; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_daddr; int /*<<< orphan*/  sk_v6_rcv_saddr; } ;
struct net {int dummy; } ;
struct inet_sock {scalar_t__ inet_dport; } ;
struct in6_addr {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {unsigned short udp_port_hash; } ;

/* Variables and functions */
 scalar_t__ PF_INET6 ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int udp_sk_bound_dev_eq (struct net*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int compute_score(struct sock *sk, struct net *net,
			 const struct in6_addr *saddr, __be16 sport,
			 const struct in6_addr *daddr, unsigned short hnum,
			 int dif, int sdif)
{
	int score;
	struct inet_sock *inet;
	bool dev_match;

	if (!net_eq(sock_net(sk), net) ||
	    udp_sk(sk)->udp_port_hash != hnum ||
	    sk->sk_family != PF_INET6)
		return -1;

	if (!ipv6_addr_equal(&sk->sk_v6_rcv_saddr, daddr))
		return -1;

	score = 0;
	inet = inet_sk(sk);

	if (inet->inet_dport) {
		if (inet->inet_dport != sport)
			return -1;
		score++;
	}

	if (!ipv6_addr_any(&sk->sk_v6_daddr)) {
		if (!ipv6_addr_equal(&sk->sk_v6_daddr, saddr))
			return -1;
		score++;
	}

	dev_match = udp_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif);
	if (!dev_match)
		return -1;
	score++;

	if (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
		score++;

	return score;
}