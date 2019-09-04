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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {int /*<<< orphan*/  reqseq; int /*<<< orphan*/  poll; } ;
struct l2cap_chan {int /*<<< orphan*/  conn_state; scalar_t__ unacked_frames; int /*<<< orphan*/  next_tx_seq; int /*<<< orphan*/ * tx_send_head; int /*<<< orphan*/  tx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int EPROTO ; 
 int /*<<< orphan*/  L2CAP_EV_RECV_IFRAME ; 
 int l2cap_finish_move (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_process_reqseq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int l2cap_rx_state_recv (struct l2cap_chan*,struct l2cap_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_i_or_rr_or_rnr (struct l2cap_chan*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_rx_state_wait_p(struct l2cap_chan *chan,
				 struct l2cap_ctrl *control,
				 struct sk_buff *skb, u8 event)
{
	int err;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	if (!control->poll)
		return -EPROTO;

	l2cap_process_reqseq(chan, control->reqseq);

	if (!skb_queue_empty(&chan->tx_q))
		chan->tx_send_head = skb_peek(&chan->tx_q);
	else
		chan->tx_send_head = NULL;

	/* Rewind next_tx_seq to the point expected
	 * by the receiver.
	 */
	chan->next_tx_seq = control->reqseq;
	chan->unacked_frames = 0;

	err = l2cap_finish_move(chan);
	if (err)
		return err;

	set_bit(CONN_SEND_FBIT, &chan->conn_state);
	l2cap_send_i_or_rr_or_rnr(chan);

	if (event == L2CAP_EV_RECV_IFRAME)
		return -EPROTO;

	return l2cap_rx_state_recv(chan, control, NULL, event);
}