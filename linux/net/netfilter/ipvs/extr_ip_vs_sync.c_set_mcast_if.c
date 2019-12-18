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
struct sock {scalar_t__ sk_bound_dev_if; scalar_t__ sk_family; } ;
struct net_device {scalar_t__ ifindex; } ;
struct ipv6_pinfo {scalar_t__ mcast_oif; } ;
struct inet_sock {scalar_t__ mc_index; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int set_mcast_if(struct sock *sk, struct net_device *dev)
{
	struct inet_sock *inet = inet_sk(sk);

	if (sk->sk_bound_dev_if && dev->ifindex != sk->sk_bound_dev_if)
		return -EINVAL;

	lock_sock(sk);
	inet->mc_index = dev->ifindex;
	/*  inet->mc_addr  = 0; */
#ifdef CONFIG_IP_VS_IPV6
	if (sk->sk_family == AF_INET6) {
		struct ipv6_pinfo *np = inet6_sk(sk);

		/* IPV6_MULTICAST_IF */
		np->mcast_oif = dev->ifindex;
	}
#endif
	release_sock(sk);

	return 0;
}