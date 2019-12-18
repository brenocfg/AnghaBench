#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_8__ {int probe_seq_end; } ;
struct tcp_sock {int sacked_out; int snd_nxt; int snd_una; int retrans_out; int high_seq; scalar_t__ delivered; int lost_out; int snd_up; int mss_cache; scalar_t__ packets_out; int /*<<< orphan*/  tcp_mstamp; int /*<<< orphan*/  lost_cnt_hint; TYPE_2__ mtu_probe; struct sk_buff* lost_skb_hint; struct sk_buff* retransmit_skb_hint; scalar_t__ retrans_stamp; } ;
struct TYPE_10__ {int in_flight; } ;
struct tcp_skb_cb {int seq; int sacked; int end_seq; int tcp_flags; TYPE_4__ tx; } ;
struct tcp_sacktag_state {int first_sackt; int last_sackt; TYPE_5__* rate; } ;
struct sock {int /*<<< orphan*/  tcp_rtx_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {scalar_t__ probe_size; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_ca_state; TYPE_3__* icsk_ca_ops; TYPE_1__ icsk_mtup; } ;
struct ack_sample {int pkts_acked; int in_flight; int /*<<< orphan*/  rtt_us; } ;
struct TYPE_11__ {scalar_t__ prior_delivered; int /*<<< orphan*/  rtt_us; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* pkts_acked ) (struct sock*,struct ack_sample*) ;} ;

/* Variables and functions */
 int FLAG_ACKED ; 
 int FLAG_ACK_MAYBE_DELAYED ; 
 int FLAG_CA_ALERT ; 
 int FLAG_DATA_ACKED ; 
 int FLAG_ORIG_SACK_ACKED ; 
 int FLAG_RETRANS_DATA_ACKED ; 
 int FLAG_SACK_RENEGING ; 
 int FLAG_SET_XMIT_TIMER ; 
 int FLAG_SYN_ACKED ; 
 int TCPCB_LOST ; 
 int TCPCB_RETRANS ; 
 int TCPCB_SACKED_ACKED ; 
 int TCPCB_SACKED_RETRANS ; 
 int TCPHDR_SYN ; 
 int /*<<< orphan*/  TCP_CHRONO_BUSY ; 
 struct tcp_skb_cb* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ after (int,int) ; 
 scalar_t__ before (int const,int) ; 
 int between (int,int,int) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_rb_first (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_rb_next (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct ack_sample*) ; 
 int /*<<< orphan*/  tcp_ack_tstamp (struct sock*,struct sk_buff*,int) ; 
 int tcp_ack_update_rtt (struct sock*,int,long,long,long,TYPE_5__*) ; 
 int /*<<< orphan*/  tcp_check_sack_reordering (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_chrono_stop (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 scalar_t__ tcp_is_sack (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mtup_probe_success (struct sock*) ; 
 int /*<<< orphan*/  tcp_rack_advance (struct tcp_sock*,int,int,int) ; 
 int /*<<< orphan*/  tcp_rate_skb_delivered (struct sock*,struct sk_buff*,TYPE_5__*) ; 
 int /*<<< orphan*/  tcp_remove_reno_sacks (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_rtx_queue_unlink_and_free (struct sk_buff*,struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_skb_pcount (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_skb_spurious_retrans (struct tcp_sock*,struct sk_buff*) ; 
 int tcp_skb_timestamp_us (struct sk_buff*) ; 
 long tcp_stamp_us_delta (int /*<<< orphan*/ ,int) ; 
 int tcp_tso_acked (struct sock*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcp_clean_rtx_queue(struct sock *sk, u32 prior_fack,
			       u32 prior_snd_una,
			       struct tcp_sacktag_state *sack)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	u64 first_ackt, last_ackt;
	struct tcp_sock *tp = tcp_sk(sk);
	u32 prior_sacked = tp->sacked_out;
	u32 reord = tp->snd_nxt; /* lowest acked un-retx un-sacked seq */
	struct sk_buff *skb, *next;
	bool fully_acked = true;
	long sack_rtt_us = -1L;
	long seq_rtt_us = -1L;
	long ca_rtt_us = -1L;
	u32 pkts_acked = 0;
	u32 last_in_flight = 0;
	bool rtt_update;
	int flag = 0;

	first_ackt = 0;

	for (skb = skb_rb_first(&sk->tcp_rtx_queue); skb; skb = next) {
		struct tcp_skb_cb *scb = TCP_SKB_CB(skb);
		const u32 start_seq = scb->seq;
		u8 sacked = scb->sacked;
		u32 acked_pcount;

		tcp_ack_tstamp(sk, skb, prior_snd_una);

		/* Determine how many packets and what bytes were acked, tso and else */
		if (after(scb->end_seq, tp->snd_una)) {
			if (tcp_skb_pcount(skb) == 1 ||
			    !after(tp->snd_una, scb->seq))
				break;

			acked_pcount = tcp_tso_acked(sk, skb);
			if (!acked_pcount)
				break;
			fully_acked = false;
		} else {
			acked_pcount = tcp_skb_pcount(skb);
		}

		if (unlikely(sacked & TCPCB_RETRANS)) {
			if (sacked & TCPCB_SACKED_RETRANS)
				tp->retrans_out -= acked_pcount;
			flag |= FLAG_RETRANS_DATA_ACKED;
		} else if (!(sacked & TCPCB_SACKED_ACKED)) {
			last_ackt = tcp_skb_timestamp_us(skb);
			WARN_ON_ONCE(last_ackt == 0);
			if (!first_ackt)
				first_ackt = last_ackt;

			last_in_flight = TCP_SKB_CB(skb)->tx.in_flight;
			if (before(start_seq, reord))
				reord = start_seq;
			if (!after(scb->end_seq, tp->high_seq))
				flag |= FLAG_ORIG_SACK_ACKED;
		}

		if (sacked & TCPCB_SACKED_ACKED) {
			tp->sacked_out -= acked_pcount;
		} else if (tcp_is_sack(tp)) {
			tp->delivered += acked_pcount;
			if (!tcp_skb_spurious_retrans(tp, skb))
				tcp_rack_advance(tp, sacked, scb->end_seq,
						 tcp_skb_timestamp_us(skb));
		}
		if (sacked & TCPCB_LOST)
			tp->lost_out -= acked_pcount;

		tp->packets_out -= acked_pcount;
		pkts_acked += acked_pcount;
		tcp_rate_skb_delivered(sk, skb, sack->rate);

		/* Initial outgoing SYN's get put onto the write_queue
		 * just like anything else we transmit.  It is not
		 * true data, and if we misinform our callers that
		 * this ACK acks real data, we will erroneously exit
		 * connection startup slow start one packet too
		 * quickly.  This is severely frowned upon behavior.
		 */
		if (likely(!(scb->tcp_flags & TCPHDR_SYN))) {
			flag |= FLAG_DATA_ACKED;
		} else {
			flag |= FLAG_SYN_ACKED;
			tp->retrans_stamp = 0;
		}

		if (!fully_acked)
			break;

		next = skb_rb_next(skb);
		if (unlikely(skb == tp->retransmit_skb_hint))
			tp->retransmit_skb_hint = NULL;
		if (unlikely(skb == tp->lost_skb_hint))
			tp->lost_skb_hint = NULL;
		tcp_rtx_queue_unlink_and_free(skb, sk);
	}

	if (!skb)
		tcp_chrono_stop(sk, TCP_CHRONO_BUSY);

	if (likely(between(tp->snd_up, prior_snd_una, tp->snd_una)))
		tp->snd_up = tp->snd_una;

	if (skb && (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_ACKED))
		flag |= FLAG_SACK_RENEGING;

	if (likely(first_ackt) && !(flag & FLAG_RETRANS_DATA_ACKED)) {
		seq_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, first_ackt);
		ca_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, last_ackt);

		if (pkts_acked == 1 && last_in_flight < tp->mss_cache &&
		    last_in_flight && !prior_sacked && fully_acked &&
		    sack->rate->prior_delivered + 1 == tp->delivered &&
		    !(flag & (FLAG_CA_ALERT | FLAG_SYN_ACKED))) {
			/* Conservatively mark a delayed ACK. It's typically
			 * from a lone runt packet over the round trip to
			 * a receiver w/o out-of-order or CE events.
			 */
			flag |= FLAG_ACK_MAYBE_DELAYED;
		}
	}
	if (sack->first_sackt) {
		sack_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, sack->first_sackt);
		ca_rtt_us = tcp_stamp_us_delta(tp->tcp_mstamp, sack->last_sackt);
	}
	rtt_update = tcp_ack_update_rtt(sk, flag, seq_rtt_us, sack_rtt_us,
					ca_rtt_us, sack->rate);

	if (flag & FLAG_ACKED) {
		flag |= FLAG_SET_XMIT_TIMER;  /* set TLP or RTO timer */
		if (unlikely(icsk->icsk_mtup.probe_size &&
			     !after(tp->mtu_probe.probe_seq_end, tp->snd_una))) {
			tcp_mtup_probe_success(sk);
		}

		if (tcp_is_reno(tp)) {
			tcp_remove_reno_sacks(sk, pkts_acked);

			/* If any of the cumulatively ACKed segments was
			 * retransmitted, non-SACK case cannot confirm that
			 * progress was due to original transmission due to
			 * lack of TCPCB_SACKED_ACKED bits even if some of
			 * the packets may have been never retransmitted.
			 */
			if (flag & FLAG_RETRANS_DATA_ACKED)
				flag &= ~FLAG_ORIG_SACK_ACKED;
		} else {
			int delta;

			/* Non-retransmitted hole got filled? That's reordering */
			if (before(reord, prior_fack))
				tcp_check_sack_reordering(sk, reord, 0);

			delta = prior_sacked - tp->sacked_out;
			tp->lost_cnt_hint -= min(tp->lost_cnt_hint, delta);
		}
	} else if (skb && rtt_update && sack_rtt_us >= 0 &&
		   sack_rtt_us > tcp_stamp_us_delta(tp->tcp_mstamp,
						    tcp_skb_timestamp_us(skb))) {
		/* Do not re-arm RTO if the sack RTT is measured from data sent
		 * after when the head was last (re)transmitted. Otherwise the
		 * timeout may continue to extend in loss recovery.
		 */
		flag |= FLAG_SET_XMIT_TIMER;  /* set TLP or RTO timer */
	}

	if (icsk->icsk_ca_ops->pkts_acked) {
		struct ack_sample sample = { .pkts_acked = pkts_acked,
					     .rtt_us = sack->rate->rtt_us,
					     .in_flight = last_in_flight };

		icsk->icsk_ca_ops->pkts_acked(sk, &sample);
	}

#if FASTRETRANS_DEBUG > 0
	WARN_ON((int)tp->sacked_out < 0);
	WARN_ON((int)tp->lost_out < 0);
	WARN_ON((int)tp->retrans_out < 0);
	if (!tp->packets_out && tcp_is_sack(tp)) {
		icsk = inet_csk(sk);
		if (tp->lost_out) {
			pr_debug("Leak l=%u %d\n",
				 tp->lost_out, icsk->icsk_ca_state);
			tp->lost_out = 0;
		}
		if (tp->sacked_out) {
			pr_debug("Leak s=%u %d\n",
				 tp->sacked_out, icsk->icsk_ca_state);
			tp->sacked_out = 0;
		}
		if (tp->retrans_out) {
			pr_debug("Leak r=%u %d\n",
				 tp->retrans_out, icsk->icsk_ca_state);
			tp->retrans_out = 0;
		}
	}
#endif
	return flag;
}