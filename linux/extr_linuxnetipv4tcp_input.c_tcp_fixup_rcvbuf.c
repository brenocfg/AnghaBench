#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sock {int sk_rcvbuf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sysctl_tcp_rmem; scalar_t__ sysctl_tcp_moderate_rcvbuf; } ;
struct TYPE_6__ {TYPE_1__ ipv4; } ;
struct TYPE_5__ {scalar_t__ advmss; } ;

/* Variables and functions */
 scalar_t__ MAX_TCP_HEADER ; 
 int SKB_TRUESIZE (scalar_t__) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* sock_net (struct sock*) ; 
 int tcp_default_init_rwnd (scalar_t__) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_fixup_rcvbuf(struct sock *sk)
{
	u32 mss = tcp_sk(sk)->advmss;
	int rcvmem;

	rcvmem = 2 * SKB_TRUESIZE(mss + MAX_TCP_HEADER) *
		 tcp_default_init_rwnd(mss);

	/* Dynamic Right Sizing (DRS) has 2 to 3 RTT latency
	 * Allow enough cushion so that sender is not limited by our window
	 */
	if (sock_net(sk)->ipv4.sysctl_tcp_moderate_rcvbuf)
		rcvmem <<= 2;

	if (sk->sk_rcvbuf < rcvmem)
		sk->sk_rcvbuf = min(rcvmem, sock_net(sk)->ipv4.sysctl_tcp_rmem[2]);
}