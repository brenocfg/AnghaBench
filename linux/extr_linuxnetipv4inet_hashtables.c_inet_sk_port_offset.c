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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_daddr; int /*<<< orphan*/  inet_rcv_saddr; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  secure_ipv4_port_ephemeral (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 inet_sk_port_offset(const struct sock *sk)
{
	const struct inet_sock *inet = inet_sk(sk);

	return secure_ipv4_port_ephemeral(inet->inet_rcv_saddr,
					  inet->inet_daddr,
					  inet->inet_dport);
}