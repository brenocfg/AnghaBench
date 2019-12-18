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
struct sock {scalar_t__ sk_family; } ;
struct ipv6_pinfo {int pmtudisc; } ;
struct inet_sock {int pmtudisc; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static void set_mcast_pmtudisc(struct sock *sk, int val)
{
	struct inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOL_IP, IP_MTU_DISCOVER, &val, sizeof(val)); */
	lock_sock(sk);
	inet->pmtudisc = val;
#ifdef CONFIG_IP_VS_IPV6
	if (sk->sk_family == AF_INET6) {
		struct ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MTU_DISCOVER */
		np->pmtudisc = val;
	}
#endif
	release_sock(sk);
}