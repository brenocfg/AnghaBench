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
typedef  void* u32 ;
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct TYPE_2__ {int ato; void* lrcvtime; } ;
struct inet_connection_sock {int icsk_rto; TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 int TCP_ATO_MIN ; 
 int /*<<< orphan*/  TCP_MAX_QUICKACKS ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_schedule_ack (struct sock*) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  tcp_ecn_check_ce (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_grow_window (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_incr_quickack (struct sock*,int /*<<< orphan*/ ) ; 
 void* tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_measure_rcv_mss (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_rcv_rtt_measure (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_event_data_recv(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	u32 now;

	inet_csk_schedule_ack(sk);

	tcp_measure_rcv_mss(sk, skb);

	tcp_rcv_rtt_measure(tp);

	now = tcp_jiffies32;

	if (!icsk->icsk_ack.ato) {
		/* The _first_ data packet received, initialize
		 * delayed ACK engine.
		 */
		tcp_incr_quickack(sk, TCP_MAX_QUICKACKS);
		icsk->icsk_ack.ato = TCP_ATO_MIN;
	} else {
		int m = now - icsk->icsk_ack.lrcvtime;

		if (m <= TCP_ATO_MIN / 2) {
			/* The fastest case is the first. */
			icsk->icsk_ack.ato = (icsk->icsk_ack.ato >> 1) + TCP_ATO_MIN / 2;
		} else if (m < icsk->icsk_ack.ato) {
			icsk->icsk_ack.ato = (icsk->icsk_ack.ato >> 1) + m;
			if (icsk->icsk_ack.ato > icsk->icsk_rto)
				icsk->icsk_ack.ato = icsk->icsk_rto;
		} else if (m > icsk->icsk_rto) {
			/* Too long gap. Apparently sender failed to
			 * restart window, so that we send ACKs quickly.
			 */
			tcp_incr_quickack(sk, TCP_MAX_QUICKACKS);
			sk_mem_reclaim(sk);
		}
	}
	icsk->icsk_ack.lrcvtime = now;

	tcp_ecn_check_ce(sk, skb);

	if (skb->len >= 128)
		tcp_grow_window(sk, skb);
}