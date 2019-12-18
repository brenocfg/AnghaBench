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
struct TYPE_5__ {int /*<<< orphan*/  snd_wscale; } ;
struct tcp_sock {scalar_t__ pred_flags; int /*<<< orphan*/  snd_wnd; TYPE_2__ rx_opt; void* lsndtime; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {void* lrcvtime; } ;
struct inet_connection_sock {TYPE_1__* icsk_af_ops; TYPE_3__ icsk_ack; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sk_rx_dst_set ) (struct sock*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB ; 
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  __tcp_fast_path_on (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keepalive_time_when (struct tcp_sock*) ; 
 int /*<<< orphan*/  security_inet_conn_established (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sk_mark_napi_id (struct sock*,struct sk_buff*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_init_transfer (struct sock*,int /*<<< orphan*/ ) ; 
 void* tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_finish_connect(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	tcp_set_state(sk, TCP_ESTABLISHED);
	icsk->icsk_ack.lrcvtime = tcp_jiffies32;

	if (skb) {
		icsk->icsk_af_ops->sk_rx_dst_set(sk, skb);
		security_inet_conn_established(sk, skb);
		sk_mark_napi_id(sk, skb);
	}

	tcp_init_transfer(sk, BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB);

	/* Prevent spurious tcp_cwnd_restart() on first data
	 * packet.
	 */
	tp->lsndtime = tcp_jiffies32;

	if (sock_flag(sk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_timer(sk, keepalive_time_when(tp));

	if (!tp->rx_opt.snd_wscale)
		__tcp_fast_path_on(tp, tp->snd_wnd);
	else
		tp->pred_flags = 0;
}