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
typedef  int /*<<< orphan*/  u16 ;
struct sock {int /*<<< orphan*/  sk_v6_rcv_saddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_num; } ;

/* Variables and functions */
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_portaddr_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  udp_lib_rehash (struct sock*,int /*<<< orphan*/ ) ; 

void udp_v6_rehash(struct sock *sk)
{
	u16 new_hash = ipv6_portaddr_hash(sock_net(sk),
					  &sk->sk_v6_rcv_saddr,
					  inet_sk(sk)->inet_num);

	udp_lib_rehash(sk, new_hash);
}