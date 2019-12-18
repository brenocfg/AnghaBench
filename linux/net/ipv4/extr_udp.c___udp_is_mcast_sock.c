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
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct net {int dummy; } ;
struct inet_sock {scalar_t__ inet_daddr; scalar_t__ inet_dport; scalar_t__ inet_rcv_saddr; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {unsigned short udp_port_hash; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_mc_sf_allow (struct sock*,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ ipv6_only_sock (struct sock*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 TYPE_1__* udp_sk (struct sock*) ; 
 int /*<<< orphan*/  udp_sk_bound_dev_eq (struct net*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline bool __udp_is_mcast_sock(struct net *net, struct sock *sk,
				       __be16 loc_port, __be32 loc_addr,
				       __be16 rmt_port, __be32 rmt_addr,
				       int dif, int sdif, unsigned short hnum)
{
	struct inet_sock *inet = inet_sk(sk);

	if (!net_eq(sock_net(sk), net) ||
	    udp_sk(sk)->udp_port_hash != hnum ||
	    (inet->inet_daddr && inet->inet_daddr != rmt_addr) ||
	    (inet->inet_dport != rmt_port && inet->inet_dport) ||
	    (inet->inet_rcv_saddr && inet->inet_rcv_saddr != loc_addr) ||
	    ipv6_only_sock(sk) ||
	    !udp_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif))
		return false;
	if (!ip_mc_sf_allow(sk, loc_addr, rmt_addr, dif, sdif))
		return false;
	return true;
}