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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct l2cap_chan {scalar_t__ unacked_frames; int /*<<< orphan*/  expected_ack_seq; int /*<<< orphan*/  tx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  __clear_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __next_seq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_process_reqseq(struct l2cap_chan *chan, u16 reqseq)
{
	struct sk_buff *acked_skb;
	u16 ackseq;

	BT_DBG("chan %p, reqseq %u", chan, reqseq);

	if (chan->unacked_frames == 0 || reqseq == chan->expected_ack_seq)
		return;

	BT_DBG("expected_ack_seq %u, unacked_frames %u",
	       chan->expected_ack_seq, chan->unacked_frames);

	for (ackseq = chan->expected_ack_seq; ackseq != reqseq;
	     ackseq = __next_seq(chan, ackseq)) {

		acked_skb = l2cap_ertm_seq_in_queue(&chan->tx_q, ackseq);
		if (acked_skb) {
			skb_unlink(acked_skb, &chan->tx_q);
			kfree_skb(acked_skb);
			chan->unacked_frames--;
		}
	}

	chan->expected_ack_seq = reqseq;

	if (chan->unacked_frames == 0)
		__clear_retrans_timer(chan);

	BT_DBG("unacked_frames %u", chan->unacked_frames);
}