#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_state; } ;
struct TYPE_3__ {scalar_t__ rcv_nxt; scalar_t__ snd_wl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPWINPROBE ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  tcp_mstamp_refresh (TYPE_1__*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_xmit_probe_skb (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void tcp_send_window_probe(struct sock *sk)
{
	if (sk->sk_state == TCP_ESTABLISHED) {
		tcp_sk(sk)->snd_wl1 = tcp_sk(sk)->rcv_nxt - 1;
		tcp_mstamp_refresh(tcp_sk(sk));
		tcp_xmit_probe_skb(sk, 0, LINUX_MIB_TCPWINPROBE);
	}
}