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
struct sock {unsigned short const sk_num; scalar_t__ const sk_rcv_saddr; scalar_t__ sk_family; int /*<<< orphan*/  sk_incoming_cpu; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_sk_bound_dev_eq (struct net*,int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  ipv6_only_sock (struct sock*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static inline int compute_score(struct sock *sk, struct net *net,
				const unsigned short hnum, const __be32 daddr,
				const int dif, const int sdif, bool exact_dif)
{
	int score = -1;

	if (net_eq(sock_net(sk), net) && sk->sk_num == hnum &&
			!ipv6_only_sock(sk)) {
		if (sk->sk_rcv_saddr != daddr)
			return -1;

		if (!inet_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif))
			return -1;

		score = sk->sk_family == PF_INET ? 2 : 1;
		if (READ_ONCE(sk->sk_incoming_cpu) == raw_smp_processor_id())
			score++;
	}
	return score;
}