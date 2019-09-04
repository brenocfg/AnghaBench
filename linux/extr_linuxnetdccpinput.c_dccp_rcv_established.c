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
struct sk_buff {int dummy; } ;
struct dccp_hdr {int dummy; } ;

/* Variables and functions */
 int __dccp_rcv_established (struct sock*,struct sk_buff*,struct dccp_hdr const*,unsigned int const) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 scalar_t__ dccp_check_seqno (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_deliver_input_to_ccids (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_handle_ackvec_processing (struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_parse_options (struct sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 

int dccp_rcv_established(struct sock *sk, struct sk_buff *skb,
			 const struct dccp_hdr *dh, const unsigned int len)
{
	if (dccp_check_seqno(sk, skb))
		goto discard;

	if (dccp_parse_options(sk, NULL, skb))
		return 1;

	dccp_handle_ackvec_processing(sk, skb);
	dccp_deliver_input_to_ccids(sk, skb);

	return __dccp_rcv_established(sk, skb, dh, len);
discard:
	__kfree_skb(skb);
	return 0;
}