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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_timestamp_echo; scalar_t__ dccps_hc_rx_insert_options; int /*<<< orphan*/  dccps_hc_rx_ccid; scalar_t__ dccps_send_ndp_count; } ;
struct TYPE_2__ {scalar_t__ dccpd_type; scalar_t__ dccpd_opt_len; } ;

/* Variables and functions */
 scalar_t__ DCCP_PKT_DATA ; 
 scalar_t__ DCCP_PKT_REQUEST ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ ccid_hc_rx_insert_options (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_ackvec_pending (struct sock*) ; 
 scalar_t__ dccp_feat_insert_opts (struct dccp_sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_ackvec (struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_ndp (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_insert_option_padding (struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_timestamp (struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_timestamp_echo (struct dccp_sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

int dccp_insert_options(struct sock *sk, struct sk_buff *skb)
{
	struct dccp_sock *dp = dccp_sk(sk);

	DCCP_SKB_CB(skb)->dccpd_opt_len = 0;

	if (dp->dccps_send_ndp_count && dccp_insert_option_ndp(sk, skb))
		return -1;

	if (DCCP_SKB_CB(skb)->dccpd_type != DCCP_PKT_DATA) {

		/* Feature Negotiation */
		if (dccp_feat_insert_opts(dp, NULL, skb))
			return -1;

		if (DCCP_SKB_CB(skb)->dccpd_type == DCCP_PKT_REQUEST) {
			/*
			 * Obtain RTT sample from Request/Response exchange.
			 * This is currently used for TFRC initialisation.
			 */
			if (dccp_insert_option_timestamp(skb))
				return -1;

		} else if (dccp_ackvec_pending(sk) &&
			   dccp_insert_option_ackvec(sk, skb)) {
				return -1;
		}
	}

	if (dp->dccps_hc_rx_insert_options) {
		if (ccid_hc_rx_insert_options(dp->dccps_hc_rx_ccid, sk, skb))
			return -1;
		dp->dccps_hc_rx_insert_options = 0;
	}

	if (dp->dccps_timestamp_echo != 0 &&
	    dccp_insert_option_timestamp_echo(dp, NULL, skb))
		return -1;

	dccp_insert_option_padding(skb);
	return 0;
}