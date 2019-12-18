#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {int /*<<< orphan*/  reqseq; int /*<<< orphan*/  final; } ;
struct l2cap_chan {TYPE_5__* conn; TYPE_2__* hs_hcon; scalar_t__ unacked_frames; int /*<<< orphan*/  next_tx_seq; int /*<<< orphan*/ * tx_send_head; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  conn_state; } ;
struct TYPE_10__ {TYPE_4__* hcon; int /*<<< orphan*/  mtu; } ;
struct TYPE_9__ {TYPE_3__* hdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  acl_mtu; } ;
struct TYPE_7__ {TYPE_1__* hdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  block_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int EPROTO ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_RECV ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_process_reqseq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int l2cap_resegment (struct l2cap_chan*) ; 
 int l2cap_rx_state_recv (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_rx_state_wait_f(struct l2cap_chan *chan,
				 struct l2cap_ctrl *control,
				 struct sk_buff *skb, u8 event)
{
	int err;

	if (!control->final)
		return -EPROTO;

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	chan->rx_state = L2CAP_RX_STATE_RECV;
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

	if (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->block_mtu;
	else
		chan->conn->mtu = chan->conn->hcon->hdev->acl_mtu;

	err = l2cap_resegment(chan);

	if (!err)
		err = l2cap_rx_state_recv(chan, control, skb, event);

	return err;
}