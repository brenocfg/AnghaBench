#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_3__ {int /*<<< orphan*/  s6_addr32; } ;
struct sock {TYPE_2__ sk_v6_daddr; TYPE_1__ sk_v6_rcv_saddr; } ;
struct inet_sock {int /*<<< orphan*/  inet_dport; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  secure_ipv6_port_ephemeral (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 inet6_sk_port_offset(const struct sock *sk)
{
	const struct inet_sock *inet = inet_sk(sk);

	return secure_ipv6_port_ephemeral(sk->sk_v6_rcv_saddr.s6_addr32,
					  sk->sk_v6_daddr.s6_addr32,
					  inet->inet_dport);
}