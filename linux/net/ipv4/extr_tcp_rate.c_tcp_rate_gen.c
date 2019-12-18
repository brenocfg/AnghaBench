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
typedef  int u64 ;
typedef  void* u32 ;
struct TYPE_3__ {int /*<<< orphan*/  sack_ok; } ;
struct tcp_sock {int delivered; int rate_interval_us; int rate_delivered; scalar_t__ rate_app_limited; TYPE_1__ rx_opt; int /*<<< orphan*/  tcp_mstamp; int /*<<< orphan*/  delivered_mstamp; scalar_t__ app_limited; } ;
struct sock {int dummy; } ;
struct rate_sample {int delivered; int interval_us; int prior_delivered; scalar_t__ is_app_limited; int /*<<< orphan*/  is_retrans; void* rcv_interval_us; void* snd_interval_us; int /*<<< orphan*/  prior_mstamp; void* losses; void* acked_sacked; } ;
struct TYPE_4__ {int /*<<< orphan*/  icsk_ca_state; } ;

/* Variables and functions */
 scalar_t__ after (int,scalar_t__) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int max (void*,void*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tcp_min_rtt (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 void* tcp_stamp_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void tcp_rate_gen(struct sock *sk, u32 delivered, u32 lost,
		  bool is_sack_reneg, struct rate_sample *rs)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u32 snd_us, ack_us;

	/* Clear app limited if bubble is acked and gone. */
	if (tp->app_limited && after(tp->delivered, tp->app_limited))
		tp->app_limited = 0;

	/* TODO: there are multiple places throughout tcp_ack() to get
	 * current time. Refactor the code using a new "tcp_acktag_state"
	 * to carry current time, flags, stats like "tcp_sacktag_state".
	 */
	if (delivered)
		tp->delivered_mstamp = tp->tcp_mstamp;

	rs->acked_sacked = delivered;	/* freshly ACKed or SACKed */
	rs->losses = lost;		/* freshly marked lost */
	/* Return an invalid sample if no timing information is available or
	 * in recovery from loss with SACK reneging. Rate samples taken during
	 * a SACK reneging event may overestimate bw by including packets that
	 * were SACKed before the reneg.
	 */
	if (!rs->prior_mstamp || is_sack_reneg) {
		rs->delivered = -1;
		rs->interval_us = -1;
		return;
	}
	rs->delivered   = tp->delivered - rs->prior_delivered;

	/* Model sending data and receiving ACKs as separate pipeline phases
	 * for a window. Usually the ACK phase is longer, but with ACK
	 * compression the send phase can be longer. To be safe we use the
	 * longer phase.
	 */
	snd_us = rs->interval_us;				/* send phase */
	ack_us = tcp_stamp_us_delta(tp->tcp_mstamp,
				    rs->prior_mstamp); /* ack phase */
	rs->interval_us = max(snd_us, ack_us);

	/* Record both segment send and ack receive intervals */
	rs->snd_interval_us = snd_us;
	rs->rcv_interval_us = ack_us;

	/* Normally we expect interval_us >= min-rtt.
	 * Note that rate may still be over-estimated when a spuriously
	 * retransmistted skb was first (s)acked because "interval_us"
	 * is under-estimated (up to an RTT). However continuously
	 * measuring the delivery rate during loss recovery is crucial
	 * for connections suffer heavy or prolonged losses.
	 */
	if (unlikely(rs->interval_us < tcp_min_rtt(tp))) {
		if (!rs->is_retrans)
			pr_debug("tcp rate: %ld %d %u %u %u\n",
				 rs->interval_us, rs->delivered,
				 inet_csk(sk)->icsk_ca_state,
				 tp->rx_opt.sack_ok, tcp_min_rtt(tp));
		rs->interval_us = -1;
		return;
	}

	/* Record the last non-app-limited or the highest app-limited bw */
	if (!rs->is_app_limited ||
	    ((u64)rs->delivered * tp->rate_interval_us >=
	     (u64)tp->rate_delivered * rs->interval_us)) {
		tp->rate_delivered = rs->delivered;
		tp->rate_interval_us = rs->interval_us;
		tp->rate_app_limited = rs->is_app_limited;
	}
}