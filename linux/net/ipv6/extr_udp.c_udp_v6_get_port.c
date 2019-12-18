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
struct sock {int /*<<< orphan*/  sk_v6_rcv_saddr; } ;
struct TYPE_2__ {unsigned int udp_portaddr_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6addr_any ; 
 unsigned int ipv6_portaddr_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned short) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int udp_lib_get_port (struct sock*,unsigned short,unsigned int) ; 
 TYPE_1__* udp_sk (struct sock*) ; 

int udp_v6_get_port(struct sock *sk, unsigned short snum)
{
	unsigned int hash2_nulladdr =
		ipv6_portaddr_hash(sock_net(sk), &in6addr_any, snum);
	unsigned int hash2_partial =
		ipv6_portaddr_hash(sock_net(sk), &sk->sk_v6_rcv_saddr, 0);

	/* precompute partial secondary hash */
	udp_sk(sk)->udp_portaddr_hash = hash2_partial;
	return udp_lib_get_port(sk, snum, hash2_nulladdr);
}