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
struct tcp_sock {int total_retrans; int snd_cwnd; int /*<<< orphan*/  snd_cwnd_stamp; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;
struct inet_connection_sock {TYPE_1__* icsk_af_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rebuild_header ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_dst_get (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_call_bpf (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_init_buffer_space (struct sock*) ; 
 int /*<<< orphan*/  tcp_init_congestion_control (struct sock*) ; 
 int tcp_init_cwnd (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_init_metrics (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mtup_init (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_init_transfer(struct sock *sk, int bpf_op)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_mtup_init(sk);
	icsk->icsk_af_ops->rebuild_header(sk);
	tcp_init_metrics(sk);

	/* Initialize the congestion window to start the transfer.
	 * Cut cwnd down to 1 per RFC5681 if SYN or SYN-ACK has been
	 * retransmitted. In light of RFC6298 more aggressive 1sec
	 * initRTO, we only reset cwnd when more than 1 SYN/SYN-ACK
	 * retransmission has occurred.
	 */
	if (tp->total_retrans > 1 && tp->undo_marker)
		tp->snd_cwnd = 1;
	else
		tp->snd_cwnd = tcp_init_cwnd(tp, __sk_dst_get(sk));
	tp->snd_cwnd_stamp = tcp_jiffies32;

	tcp_call_bpf(sk, bpf_op, 0, NULL);
	tcp_init_congestion_control(sk);
	tcp_init_buffer_space(sk);
}