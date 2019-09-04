#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sock {int dummy; } ;
struct ccid2_hc_tx_sock {int tx_cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCPF_ACK_RATIO ; 
 int /*<<< orphan*/  ccid2_change_l_ack_ratio (struct sock*,unsigned int) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int dccp_feat_nn_get (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccid2_check_l_ack_ratio(struct sock *sk)
{
	struct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	/*
	 * After a loss, idle period, application limited period, or RTO we
	 * need to check that the ack ratio is still less than the congestion
	 * window. Otherwise, we will send an entire congestion window of
	 * packets and got no response because we haven't sent ack ratio
	 * packets yet.
	 * If the ack ratio does need to be reduced, we reduce it to half of
	 * the congestion window (or 1 if that's zero) instead of to the
	 * congestion window. This prevents problems if one ack is lost.
	 */
	if (dccp_feat_nn_get(sk, DCCPF_ACK_RATIO) > hc->tx_cwnd)
		ccid2_change_l_ack_ratio(sk, hc->tx_cwnd/2 ? : 1U);
}