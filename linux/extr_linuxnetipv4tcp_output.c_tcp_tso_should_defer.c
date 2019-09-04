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
typedef  int u32 ;
struct tcp_sock {int snd_cwnd; int mss_cache; int snd_wnd; int srtt_us; int /*<<< orphan*/  tcp_mstamp; scalar_t__ lsndtime; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; int /*<<< orphan*/  skb_mstamp; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {int seq; int tcp_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  sysctl_tcp_tso_win_divisor; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int TCPHDR_FIN ; 
 scalar_t__ TCP_CA_Recovery ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int min (int,int) ; 
 TYPE_2__* sock_net (struct sock*) ; 
 scalar_t__ tcp_jiffies32 ; 
 int tcp_max_tso_deferred_mss (struct tcp_sock*) ; 
 int tcp_packets_in_flight (struct tcp_sock*) ; 
 struct sk_buff* tcp_rtx_queue_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_skb_pcount (struct sk_buff*) ; 
 int tcp_stamp_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcp_wnd_end (struct tcp_sock*) ; 
 struct sk_buff* tcp_write_queue_tail (struct sock*) ; 

__attribute__((used)) static bool tcp_tso_should_defer(struct sock *sk, struct sk_buff *skb,
				 bool *is_cwnd_limited,
				 bool *is_rwnd_limited,
				 u32 max_segs)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	u32 age, send_win, cong_win, limit, in_flight;
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *head;
	int win_divisor;

	if (icsk->icsk_ca_state >= TCP_CA_Recovery)
		goto send_now;

	/* Avoid bursty behavior by allowing defer
	 * only if the last write was recent.
	 */
	if ((s32)(tcp_jiffies32 - tp->lsndtime) > 0)
		goto send_now;

	in_flight = tcp_packets_in_flight(tp);

	BUG_ON(tcp_skb_pcount(skb) <= 1);
	BUG_ON(tp->snd_cwnd <= in_flight);

	send_win = tcp_wnd_end(tp) - TCP_SKB_CB(skb)->seq;

	/* From in_flight test above, we know that cwnd > in_flight.  */
	cong_win = (tp->snd_cwnd - in_flight) * tp->mss_cache;

	limit = min(send_win, cong_win);

	/* If a full-sized TSO skb can be sent, do it. */
	if (limit >= max_segs * tp->mss_cache)
		goto send_now;

	/* Middle in queue won't get any more data, full sendable already? */
	if ((skb != tcp_write_queue_tail(sk)) && (limit >= skb->len))
		goto send_now;

	win_divisor = READ_ONCE(sock_net(sk)->ipv4.sysctl_tcp_tso_win_divisor);
	if (win_divisor) {
		u32 chunk = min(tp->snd_wnd, tp->snd_cwnd * tp->mss_cache);

		/* If at least some fraction of a window is available,
		 * just use it.
		 */
		chunk /= win_divisor;
		if (limit >= chunk)
			goto send_now;
	} else {
		/* Different approach, try not to defer past a single
		 * ACK.  Receiver should ACK every other full sized
		 * frame, so if we have space for more than 3 frames
		 * then send now.
		 */
		if (limit > tcp_max_tso_deferred_mss(tp) * tp->mss_cache)
			goto send_now;
	}

	/* TODO : use tsorted_sent_queue ? */
	head = tcp_rtx_queue_head(sk);
	if (!head)
		goto send_now;
	age = tcp_stamp_us_delta(tp->tcp_mstamp, head->skb_mstamp);
	/* If next ACK is likely to come too late (half srtt), do not defer */
	if (age < (tp->srtt_us >> 4))
		goto send_now;

	/* Ok, it looks like it is advisable to defer.
	 * Three cases are tracked :
	 * 1) We are cwnd-limited
	 * 2) We are rwnd-limited
	 * 3) We are application limited.
	 */
	if (cong_win < send_win) {
		if (cong_win <= skb->len) {
			*is_cwnd_limited = true;
			return true;
		}
	} else {
		if (send_win <= skb->len) {
			*is_rwnd_limited = true;
			return true;
		}
	}

	/* If this packet won't get more data, do not wait. */
	if (TCP_SKB_CB(skb)->tcp_flags & TCPHDR_FIN)
		goto send_now;

	return true;

send_now:
	return false;
}