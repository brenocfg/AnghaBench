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
struct tcp_sock {scalar_t__ rcv_nxt; scalar_t__ rcv_wup; int window_clamp; int /*<<< orphan*/  copied_seq; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {scalar_t__ rcv_mss; int pending; scalar_t__ blocked; } ;
struct inet_connection_sock {TYPE_1__ icsk_ack; } ;
typedef  int __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 int ICSK_ACK_PUSHED ; 
 int ICSK_ACK_PUSHED2 ; 
 int RCV_SHUTDOWN ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int __tcp_select_window (struct sock*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ inet_csk_ack_scheduled (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_in_pingpong_mode (struct sock*) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int tcp_receive_window (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_send_ack (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_cleanup_rbuf(struct sock *sk, int copied)
{
	struct tcp_sock *tp = tcp_sk(sk);
	bool time_to_ack = false;

	struct sk_buff *skb = skb_peek(&sk->sk_receive_queue);

	WARN(skb && !before(tp->copied_seq, TCP_SKB_CB(skb)->end_seq),
	     "cleanup rbuf bug: copied %X seq %X rcvnxt %X\n",
	     tp->copied_seq, TCP_SKB_CB(skb)->end_seq, tp->rcv_nxt);

	if (inet_csk_ack_scheduled(sk)) {
		const struct inet_connection_sock *icsk = inet_csk(sk);
		   /* Delayed ACKs frequently hit locked sockets during bulk
		    * receive. */
		if (icsk->icsk_ack.blocked ||
		    /* Once-per-two-segments ACK was not sent by tcp_input.c */
		    tp->rcv_nxt - tp->rcv_wup > icsk->icsk_ack.rcv_mss ||
		    /*
		     * If this read emptied read buffer, we send ACK, if
		     * connection is not bidirectional, user drained
		     * receive buffer and there was a small segment
		     * in queue.
		     */
		    (copied > 0 &&
		     ((icsk->icsk_ack.pending & ICSK_ACK_PUSHED2) ||
		      ((icsk->icsk_ack.pending & ICSK_ACK_PUSHED) &&
		       !inet_csk_in_pingpong_mode(sk))) &&
		      !atomic_read(&sk->sk_rmem_alloc)))
			time_to_ack = true;
	}

	/* We send an ACK if we can now advertise a non-zero window
	 * which has been raised "significantly".
	 *
	 * Even if window raised up to infinity, do not send window open ACK
	 * in states, where we will not receive more. It is useless.
	 */
	if (copied > 0 && !time_to_ack && !(sk->sk_shutdown & RCV_SHUTDOWN)) {
		__u32 rcv_window_now = tcp_receive_window(tp);

		/* Optimize, __tcp_select_window() is not cheap. */
		if (2*rcv_window_now <= tp->window_clamp) {
			__u32 new_window = __tcp_select_window(sk);

			/* Send ACK now, if this read freed lots of space
			 * in our buffer. Certainly, new_window is new window.
			 * We can advertise it now, if it is not less than current one.
			 * "Lots" means "at least twice" here.
			 */
			if (new_window && new_window >= 2 * rcv_window_now)
				time_to_ack = true;
		}
	}
	if (time_to_ack)
		tcp_send_ack(sk);
}