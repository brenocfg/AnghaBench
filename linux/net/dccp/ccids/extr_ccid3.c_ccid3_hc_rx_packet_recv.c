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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct ccid3_hc_rx_sock {scalar_t__ rx_state; scalar_t__ rx_s; scalar_t__ rx_rtt; int /*<<< orphan*/  rx_hist; int /*<<< orphan*/  rx_last_counter; int /*<<< orphan*/  rx_li_hist; int /*<<< orphan*/  rx_bytes_recv; } ;
typedef  enum ccid3_fback_type { ____Placeholder_ccid3_fback_type } ccid3_fback_type ;
struct TYPE_6__ {int dccph_doff; int /*<<< orphan*/  dccph_ccval; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpor_ndp; } ;
struct TYPE_5__ {TYPE_1__ dccps_options_received; } ;

/* Variables and functions */
 int CCID3_FBACK_INITIAL ; 
 int CCID3_FBACK_NONE ; 
 int CCID3_FBACK_PARAM_CHANGE ; 
 int CCID3_FBACK_PERIODIC ; 
 int SUB16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TFRC_RSTATE_DATA ; 
 scalar_t__ TFRC_RSTATE_NO_DATA ; 
 int /*<<< orphan*/  ccid3_first_li ; 
 int /*<<< orphan*/  ccid3_hc_rx_send_feedback (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  ccid3_hc_rx_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct ccid3_hc_rx_sock* ccid3_hc_rx_sk (struct sock*) ; 
 int dccp_data_packet (struct sk_buff*) ; 
 TYPE_3__* dccp_hdr (struct sk_buff*) ; 
 TYPE_2__* dccp_sk (struct sock*) ; 
 void* tfrc_ewma (scalar_t__,scalar_t__ const,int) ; 
 int /*<<< orphan*/  tfrc_lh_is_initialised (int /*<<< orphan*/ *) ; 
 scalar_t__ tfrc_lh_update_i_mean (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ tfrc_rx_handle_loss (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  tfrc_rx_hist_add_packet (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/  const) ; 
 scalar_t__ tfrc_rx_hist_duplicate (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ tfrc_rx_hist_loss_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ tfrc_rx_hist_sample_rtt (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ccid3_hc_rx_packet_recv(struct sock *sk, struct sk_buff *skb)
{
	struct ccid3_hc_rx_sock *hc = ccid3_hc_rx_sk(sk);
	enum ccid3_fback_type do_feedback = CCID3_FBACK_NONE;
	const u64 ndp = dccp_sk(sk)->dccps_options_received.dccpor_ndp;
	const bool is_data_packet = dccp_data_packet(skb);

	if (unlikely(hc->rx_state == TFRC_RSTATE_NO_DATA)) {
		if (is_data_packet) {
			const u32 payload = skb->len - dccp_hdr(skb)->dccph_doff * 4;
			do_feedback = CCID3_FBACK_INITIAL;
			ccid3_hc_rx_set_state(sk, TFRC_RSTATE_DATA);
			hc->rx_s = payload;
			/*
			 * Not necessary to update rx_bytes_recv here,
			 * since X_recv = 0 for the first feedback packet (cf.
			 * RFC 3448, 6.3) -- gerrit
			 */
		}
		goto update_records;
	}

	if (tfrc_rx_hist_duplicate(&hc->rx_hist, skb))
		return; /* done receiving */

	if (is_data_packet) {
		const u32 payload = skb->len - dccp_hdr(skb)->dccph_doff * 4;
		/*
		 * Update moving-average of s and the sum of received payload bytes
		 */
		hc->rx_s = tfrc_ewma(hc->rx_s, payload, 9);
		hc->rx_bytes_recv += payload;
	}

	/*
	 * Perform loss detection and handle pending losses
	 */
	if (tfrc_rx_handle_loss(&hc->rx_hist, &hc->rx_li_hist,
				skb, ndp, ccid3_first_li, sk)) {
		do_feedback = CCID3_FBACK_PARAM_CHANGE;
		goto done_receiving;
	}

	if (tfrc_rx_hist_loss_pending(&hc->rx_hist))
		return; /* done receiving */

	/*
	 * Handle data packets: RTT sampling and monitoring p
	 */
	if (unlikely(!is_data_packet))
		goto update_records;

	if (!tfrc_lh_is_initialised(&hc->rx_li_hist)) {
		const u32 sample = tfrc_rx_hist_sample_rtt(&hc->rx_hist, skb);
		/*
		 * Empty loss history: no loss so far, hence p stays 0.
		 * Sample RTT values, since an RTT estimate is required for the
		 * computation of p when the first loss occurs; RFC 3448, 6.3.1.
		 */
		if (sample != 0)
			hc->rx_rtt = tfrc_ewma(hc->rx_rtt, sample, 9);

	} else if (tfrc_lh_update_i_mean(&hc->rx_li_hist, skb)) {
		/*
		 * Step (3) of [RFC 3448, 6.1]: Recompute I_mean and, if I_mean
		 * has decreased (resp. p has increased), send feedback now.
		 */
		do_feedback = CCID3_FBACK_PARAM_CHANGE;
	}

	/*
	 * Check if the periodic once-per-RTT feedback is due; RFC 4342, 10.3
	 */
	if (SUB16(dccp_hdr(skb)->dccph_ccval, hc->rx_last_counter) > 3)
		do_feedback = CCID3_FBACK_PERIODIC;

update_records:
	tfrc_rx_hist_add_packet(&hc->rx_hist, skb, ndp);

done_receiving:
	if (do_feedback)
		ccid3_hc_rx_send_feedback(sk, skb, do_feedback);
}