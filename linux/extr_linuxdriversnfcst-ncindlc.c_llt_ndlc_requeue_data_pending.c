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
typedef  int u8 ;
struct sk_buff {int* data; } ;
struct llt_ndlc {int /*<<< orphan*/  send_q; int /*<<< orphan*/  ack_pending_q; } ;

/* Variables and functions */
 int PCB_DATAFRAME_RETRANSMIT_MASK ; 
 int PCB_DATAFRAME_RETRANSMIT_YES ; 
 int PCB_SUPERVISOR_RETRANSMIT_MASK ; 
 int PCB_SUPERVISOR_RETRANSMIT_YES ; 
#define  PCB_TYPE_DATAFRAME 129 
 int PCB_TYPE_MASK ; 
#define  PCB_TYPE_SUPERVISOR 128 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct sk_buff* skb_dequeue_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void llt_ndlc_requeue_data_pending(struct llt_ndlc *ndlc)
{
	struct sk_buff *skb;
	u8 pcb;

	while ((skb = skb_dequeue_tail(&ndlc->ack_pending_q))) {
		pcb = skb->data[0];
		switch (pcb & PCB_TYPE_MASK) {
		case PCB_TYPE_SUPERVISOR:
			skb->data[0] = (pcb & ~PCB_SUPERVISOR_RETRANSMIT_MASK) |
				PCB_SUPERVISOR_RETRANSMIT_YES;
			break;
		case PCB_TYPE_DATAFRAME:
			skb->data[0] = (pcb & ~PCB_DATAFRAME_RETRANSMIT_MASK) |
				PCB_DATAFRAME_RETRANSMIT_YES;
			break;
		default:
			pr_err("UNKNOWN Packet Control Byte=%d\n", pcb);
			kfree_skb(skb);
			continue;
		}
		skb_queue_head(&ndlc->send_q, skb);
	}
}