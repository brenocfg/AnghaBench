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
typedef  long u32 ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {long dccpor_timestamp_echo; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_osr; int /*<<< orphan*/  dccps_syn_rtt; TYPE_1__ dccps_options_received; } ;
struct dccp_hdr {int dccph_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_OPEN ; 
 int /*<<< orphan*/  DCCP_PARTOPEN ; 
#define  DCCP_PKT_ACK 131 
#define  DCCP_PKT_DATA 130 
#define  DCCP_PKT_DATAACK 129 
#define  DCCP_PKT_RESET 128 
 int /*<<< orphan*/  DCCP_RESPOND ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  __dccp_rcv_established (struct sock*,struct sk_buff*,struct dccp_hdr const*,unsigned int const) ; 
 int /*<<< orphan*/  dccp_sample_rtt (struct sock*,int) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 long dccp_timestamp () ; 
 int /*<<< orphan*/  inet_csk_clear_xmit_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  likely (long) ; 

__attribute__((used)) static int dccp_rcv_respond_partopen_state_process(struct sock *sk,
						   struct sk_buff *skb,
						   const struct dccp_hdr *dh,
						   const unsigned int len)
{
	struct dccp_sock *dp = dccp_sk(sk);
	u32 sample = dp->dccps_options_received.dccpor_timestamp_echo;
	int queued = 0;

	switch (dh->dccph_type) {
	case DCCP_PKT_RESET:
		inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);
		break;
	case DCCP_PKT_DATA:
		if (sk->sk_state == DCCP_RESPOND)
			break;
		/* fall through */
	case DCCP_PKT_DATAACK:
	case DCCP_PKT_ACK:
		/*
		 * FIXME: we should be resetting the PARTOPEN (DELACK) timer
		 * here but only if we haven't used the DELACK timer for
		 * something else, like sending a delayed ack for a TIMESTAMP
		 * echo, etc, for now were not clearing it, sending an extra
		 * ACK when there is nothing else to do in DELACK is not a big
		 * deal after all.
		 */

		/* Stop the PARTOPEN timer */
		if (sk->sk_state == DCCP_PARTOPEN)
			inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);

		/* Obtain usec RTT sample from SYN exchange (used by TFRC). */
		if (likely(sample)) {
			long delta = dccp_timestamp() - sample;

			dp->dccps_syn_rtt = dccp_sample_rtt(sk, 10 * delta);
		}

		dp->dccps_osr = DCCP_SKB_CB(skb)->dccpd_seq;
		dccp_set_state(sk, DCCP_OPEN);

		if (dh->dccph_type == DCCP_PKT_DATAACK ||
		    dh->dccph_type == DCCP_PKT_DATA) {
			__dccp_rcv_established(sk, skb, dh, len);
			queued = 1; /* packet was queued
				       (by __dccp_rcv_established) */
		}
		break;
	}

	return queued;
}