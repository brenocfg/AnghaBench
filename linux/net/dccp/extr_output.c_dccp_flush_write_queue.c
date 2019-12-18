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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_hc_tx_ccid; } ;

/* Variables and functions */
#define  CCID_PACKET_DELAY 131 
#define  CCID_PACKET_ERR 130 
#define  CCID_PACKET_SEND_AT_ONCE 129 
#define  CCID_PACKET_WILL_DEQUEUE_LATER 128 
 int /*<<< orphan*/  DCCP_WARN (char*) ; 
 long ccid_hc_tx_send_packet (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 int ccid_packet_dequeue_eval (long) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,long) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 long dccp_wait_for_ccid (struct sock*,long) ; 
 int /*<<< orphan*/  dccp_xmit_packet (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 long msecs_to_jiffies (long) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

void dccp_flush_write_queue(struct sock *sk, long *time_budget)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb;
	long delay, rc;

	while (*time_budget > 0 && (skb = skb_peek(&sk->sk_write_queue))) {
		rc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		switch (ccid_packet_dequeue_eval(rc)) {
		case CCID_PACKET_WILL_DEQUEUE_LATER:
			/*
			 * If the CCID determines when to send, the next sending
			 * time is unknown or the CCID may not even send again
			 * (e.g. remote host crashes or lost Ack packets).
			 */
			DCCP_WARN("CCID did not manage to send all packets\n");
			return;
		case CCID_PACKET_DELAY:
			delay = msecs_to_jiffies(rc);
			if (delay > *time_budget)
				return;
			rc = dccp_wait_for_ccid(sk, delay);
			if (rc < 0)
				return;
			*time_budget -= (delay - rc);
			/* check again if we can send now */
			break;
		case CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			break;
		case CCID_PACKET_ERR:
			skb_dequeue(&sk->sk_write_queue);
			kfree_skb(skb);
			dccp_pr_debug("packet discarded due to err=%ld\n", rc);
		}
	}
}