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
struct sk_buff {struct sk_buff* next; } ;
struct rxrpc_call {int acks_lowest_nak; int tx_hard_ack; int* rxtx_annotations; int /*<<< orphan*/  waitq; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; struct sk_buff** rxtx_buffer; } ;
struct rxrpc_ack_summary {int new_low_nack; int /*<<< orphan*/  nr_rot_new_acks; } ;
typedef  void* rxrpc_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CALL_TX_LAST ; 
 int RXRPC_RXTX_BUFF_MASK ; 
 int RXRPC_TX_ANNO_ACK ; 
 int RXRPC_TX_ANNO_LAST ; 
 int RXRPC_TX_ANNO_MASK ; 
 scalar_t__ before (int,void*) ; 
 scalar_t__ before_eq (int,void*) ; 
 int /*<<< orphan*/  rxrpc_free_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_see_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_skb_freed ; 
 int /*<<< orphan*/  rxrpc_skb_rotated ; 
 int /*<<< orphan*/  rxrpc_transmit_rotate ; 
 int /*<<< orphan*/  rxrpc_transmit_rotate_last ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_transmit (struct rxrpc_call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool rxrpc_rotate_tx_window(struct rxrpc_call *call, rxrpc_seq_t to,
				   struct rxrpc_ack_summary *summary)
{
	struct sk_buff *skb, *list = NULL;
	bool rot_last = false;
	int ix;
	u8 annotation;

	if (call->acks_lowest_nak == call->tx_hard_ack) {
		call->acks_lowest_nak = to;
	} else if (before_eq(call->acks_lowest_nak, to)) {
		summary->new_low_nack = true;
		call->acks_lowest_nak = to;
	}

	spin_lock(&call->lock);

	while (before(call->tx_hard_ack, to)) {
		call->tx_hard_ack++;
		ix = call->tx_hard_ack & RXRPC_RXTX_BUFF_MASK;
		skb = call->rxtx_buffer[ix];
		annotation = call->rxtx_annotations[ix];
		rxrpc_see_skb(skb, rxrpc_skb_rotated);
		call->rxtx_buffer[ix] = NULL;
		call->rxtx_annotations[ix] = 0;
		skb->next = list;
		list = skb;

		if (annotation & RXRPC_TX_ANNO_LAST) {
			set_bit(RXRPC_CALL_TX_LAST, &call->flags);
			rot_last = true;
		}
		if ((annotation & RXRPC_TX_ANNO_MASK) != RXRPC_TX_ANNO_ACK)
			summary->nr_rot_new_acks++;
	}

	spin_unlock(&call->lock);

	trace_rxrpc_transmit(call, (rot_last ?
				    rxrpc_transmit_rotate_last :
				    rxrpc_transmit_rotate));
	wake_up(&call->waitq);

	while (list) {
		skb = list;
		list = skb->next;
		skb_mark_not_on_list(skb);
		rxrpc_free_skb(skb, rxrpc_skb_freed);
	}

	return rot_last;
}