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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct cxgbit_sock {int /*<<< orphan*/  lock; int /*<<< orphan*/  backlogq; scalar_t__ lock_owner; scalar_t__ rx_credits; int /*<<< orphan*/  ctrlq_idx; int /*<<< orphan*/  tid; } ;
struct cpl_rx_data_ack {int dummy; } ;
typedef  int /*<<< orphan*/  (* cxgbit_skcb_rx_backlog_fn ) (struct cxgbit_sock*,struct sk_buff*) ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_CREDITS_V (scalar_t__) ; 
 int RX_DACK_CHANGE_F ; 
 int RX_DACK_MODE_V (int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct cxgbit_sock*,struct sk_buff*)) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_mk_rx_data_ack (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxgbit_send_rx_credits (struct cxgbit_sock*,struct sk_buff*) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cxgbit_rx_data_ack(struct cxgbit_sock *csk)
{
	struct sk_buff *skb;
	u32 len = roundup(sizeof(struct cpl_rx_data_ack), 16);
	u32 credit_dack;

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb)
		return -1;

	credit_dack = RX_DACK_CHANGE_F | RX_DACK_MODE_V(1) |
		      RX_CREDITS_V(csk->rx_credits);

	cxgb_mk_rx_data_ack(skb, len, csk->tid, csk->ctrlq_idx,
			    credit_dack);

	csk->rx_credits = 0;

	spin_lock_bh(&csk->lock);
	if (csk->lock_owner) {
		cxgbit_skcb_rx_backlog_fn(skb) = cxgbit_send_rx_credits;
		__skb_queue_tail(&csk->backlogq, skb);
		spin_unlock_bh(&csk->lock);
		return 0;
	}

	cxgbit_send_rx_credits(csk, skb);
	spin_unlock_bh(&csk->lock);

	return 0;
}