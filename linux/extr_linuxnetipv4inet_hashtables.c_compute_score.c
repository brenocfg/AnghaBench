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
struct sock {scalar_t__ sk_family; int const sk_bound_dev_if; scalar_t__ sk_incoming_cpu; } ;
struct net {int dummy; } ;
struct inet_sock {unsigned short const inet_num; scalar_t__ inet_rcv_saddr; } ;
typedef  scalar_t__ const __be32 ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_only_sock (struct sock*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 scalar_t__ raw_smp_processor_id () ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static inline int compute_score(struct sock *sk, struct net *net,
				const unsigned short hnum, const __be32 daddr,
				const int dif, const int sdif, bool exact_dif)
{
	int score = -1;
	struct inet_sock *inet = inet_sk(sk);

	if (net_eq(sock_net(sk), net) && inet->inet_num == hnum &&
			!ipv6_only_sock(sk)) {
		__be32 rcv_saddr = inet->inet_rcv_saddr;
		score = sk->sk_family == PF_INET ? 2 : 1;
		if (rcv_saddr) {
			if (rcv_saddr != daddr)
				return -1;
			score += 4;
		}
		if (sk->sk_bound_dev_if || exact_dif) {
			bool dev_match = (sk->sk_bound_dev_if == dif ||
					  sk->sk_bound_dev_if == sdif);

			if (!dev_match)
				return -1;
			if (sk->sk_bound_dev_if)
				score += 4;
		}
		if (sk->sk_incoming_cpu == raw_smp_processor_id())
			score++;
	}
	return score;
}