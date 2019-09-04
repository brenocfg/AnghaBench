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
struct sk_buff {int dummy; } ;
struct dccp_request_sock {scalar_t__ dreq_timestamp_echo; } ;
struct TYPE_2__ {scalar_t__ dccpd_opt_len; } ;

/* Variables and functions */
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ dccp_feat_insert_opts (int /*<<< orphan*/ *,struct dccp_request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_insert_option_padding (struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_timestamp (struct sk_buff*) ; 
 scalar_t__ dccp_insert_option_timestamp_echo (int /*<<< orphan*/ *,struct dccp_request_sock*,struct sk_buff*) ; 

int dccp_insert_options_rsk(struct dccp_request_sock *dreq, struct sk_buff *skb)
{
	DCCP_SKB_CB(skb)->dccpd_opt_len = 0;

	if (dccp_feat_insert_opts(NULL, dreq, skb))
		return -1;

	/* Obtain RTT sample from Response/Ack exchange (used by TFRC). */
	if (dccp_insert_option_timestamp(skb))
		return -1;

	if (dreq->dreq_timestamp_echo != 0 &&
	    dccp_insert_option_timestamp_echo(NULL, dreq, skb))
		return -1;

	dccp_insert_option_padding(skb);
	return 0;
}