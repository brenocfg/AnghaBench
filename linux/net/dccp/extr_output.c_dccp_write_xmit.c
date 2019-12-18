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
struct dccp_sock {int /*<<< orphan*/  dccps_xmit_timer; int /*<<< orphan*/  dccps_hc_tx_ccid; } ;

/* Variables and functions */
#define  CCID_PACKET_DELAY 131 
#define  CCID_PACKET_ERR 130 
#define  CCID_PACKET_SEND_AT_ONCE 129 
#define  CCID_PACKET_WILL_DEQUEUE_LATER 128 
 int ccid_hc_tx_send_packet (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 int ccid_packet_dequeue_eval (int) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int) ; 
 int /*<<< orphan*/  dccp_qpolicy_drop (struct sock*,struct sk_buff*) ; 
 struct sk_buff* dccp_qpolicy_top (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_xmit_packet (struct sock*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 

void dccp_write_xmit(struct sock *sk)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb;

	while ((skb = dccp_qpolicy_top(sk))) {
		int rc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		switch (ccid_packet_dequeue_eval(rc)) {
		case CCID_PACKET_WILL_DEQUEUE_LATER:
			return;
		case CCID_PACKET_DELAY:
			sk_reset_timer(sk, &dp->dccps_xmit_timer,
				       jiffies + msecs_to_jiffies(rc));
			return;
		case CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			break;
		case CCID_PACKET_ERR:
			dccp_qpolicy_drop(sk, skb);
			dccp_pr_debug("packet discarded due to err=%d\n", rc);
		}
	}
}