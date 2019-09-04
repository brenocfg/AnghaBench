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
struct l2cap_chan {int /*<<< orphan*/  rx_state; int /*<<< orphan*/  srej_q; int /*<<< orphan*/  buffer_seq; int /*<<< orphan*/  conn_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  l2cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_RECV ; 
 int /*<<< orphan*/  __next_seq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 struct sk_buff* l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int l2cap_reassemble_sdu (struct l2cap_chan*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_send_ack (struct l2cap_chan*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_rx_queued_iframes(struct l2cap_chan *chan)
{
	int err = 0;
	/* Pass sequential frames to l2cap_reassemble_sdu()
	 * until a gap is encountered.
	 */

	BT_DBG("chan %p", chan);

	while (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) {
		struct sk_buff *skb;
		BT_DBG("Searching for skb with txseq %d (queue len %d)",
		       chan->buffer_seq, skb_queue_len(&chan->srej_q));

		skb = l2cap_ertm_seq_in_queue(&chan->srej_q, chan->buffer_seq);

		if (!skb)
			break;

		skb_unlink(skb, &chan->srej_q);
		chan->buffer_seq = __next_seq(chan, chan->buffer_seq);
		err = l2cap_reassemble_sdu(chan, skb, &bt_cb(skb)->l2cap);
		if (err)
			break;
	}

	if (skb_queue_empty(&chan->srej_q)) {
		chan->rx_state = L2CAP_RX_STATE_RECV;
		l2cap_send_ack(chan);
	}

	return err;
}