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
typedef  int u32 ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int len; } ;
struct dccp_sock {int dccps_mss_cache; int /*<<< orphan*/  dccps_gsr; scalar_t__ dccps_sync_scheduled; int /*<<< orphan*/  dccps_hc_tx_ccid; int /*<<< orphan*/  dccps_featneg; } ;
struct TYPE_4__ {void* dccpd_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  icsk_rto; } ;

/* Variables and functions */
 int DCCP_FEATNEG_OVERHEAD ; 
 scalar_t__ DCCP_PARTOPEN ; 
 void* DCCP_PKT_DATA ; 
 void* DCCP_PKT_DATAACK ; 
 int /*<<< orphan*/  DCCP_PKT_SYNC ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_WARN (char*,int) ; 
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  ccid_hc_tx_packet_sent (int /*<<< orphan*/ ,struct sock*,int) ; 
 scalar_t__ dccp_ack_pending (struct sock*) ; 
 int /*<<< orphan*/  dccp_feat_list_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int) ; 
 struct sk_buff* dccp_qpolicy_pop (struct sock*) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int dccp_transmit_skb (struct sock*,struct sk_buff*) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_schedule_ack (struct sock*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_xmit_packet(struct sock *sk)
{
	int err, len;
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb = dccp_qpolicy_pop(sk);

	if (unlikely(skb == NULL))
		return;
	len = skb->len;

	if (sk->sk_state == DCCP_PARTOPEN) {
		const u32 cur_mps = dp->dccps_mss_cache - DCCP_FEATNEG_OVERHEAD;
		/*
		 * See 8.1.5 - Handshake Completion.
		 *
		 * For robustness we resend Confirm options until the client has
		 * entered OPEN. During the initial feature negotiation, the MPS
		 * is smaller than usual, reduced by the Change/Confirm options.
		 */
		if (!list_empty(&dp->dccps_featneg) && len > cur_mps) {
			DCCP_WARN("Payload too large (%d) for featneg.\n", len);
			dccp_send_ack(sk);
			dccp_feat_list_purge(&dp->dccps_featneg);
		}

		inet_csk_schedule_ack(sk);
		inet_csk_reset_xmit_timer(sk, ICSK_TIME_DACK,
					      inet_csk(sk)->icsk_rto,
					      DCCP_RTO_MAX);
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	} else if (dccp_ack_pending(sk)) {
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	} else {
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATA;
	}

	err = dccp_transmit_skb(sk, skb);
	if (err)
		dccp_pr_debug("transmit_skb() returned err=%d\n", err);
	/*
	 * Register this one as sent even if an error occurred. To the remote
	 * end a local packet drop is indistinguishable from network loss, i.e.
	 * any local drop will eventually be reported via receiver feedback.
	 */
	ccid_hc_tx_packet_sent(dp->dccps_hc_tx_ccid, sk, len);

	/*
	 * If the CCID needs to transfer additional header options out-of-band
	 * (e.g. Ack Vectors or feature-negotiation options), it activates this
	 * flag to schedule a Sync. The Sync will automatically incorporate all
	 * currently pending header options, thus clearing the backlog.
	 */
	if (dp->dccps_sync_scheduled)
		dccp_send_sync(sk, dp->dccps_gsr, DCCP_PKT_SYNC);
}