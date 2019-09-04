#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {scalar_t__ reqseq; scalar_t__ final; } ;
struct l2cap_chan {scalar_t__ next_tx_seq; scalar_t__ max_tx; scalar_t__ tx_state; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  tx_q; } ;
struct TYPE_3__ {scalar_t__ retries; } ;
struct TYPE_4__ {TYPE_1__ l2cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  CONN_REJ_ACT ; 
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int /*<<< orphan*/  ECONNRESET ; 
 scalar_t__ L2CAP_TX_STATE_WAIT_F ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 struct sk_buff* l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_pass_to_tx (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_retransmit_all (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_handle_rej(struct l2cap_chan *chan,
			     struct l2cap_ctrl *control)
{
	struct sk_buff *skb;

	BT_DBG("chan %p, control %p", chan, control);

	if (control->reqseq == chan->next_tx_seq) {
		BT_DBG("Invalid reqseq %d, disconnecting", control->reqseq);
		l2cap_send_disconn_req(chan, ECONNRESET);
		return;
	}

	skb = l2cap_ertm_seq_in_queue(&chan->tx_q, control->reqseq);

	if (chan->max_tx && skb &&
	    bt_cb(skb)->l2cap.retries >= chan->max_tx) {
		BT_DBG("Retry limit exceeded (%d)", chan->max_tx);
		l2cap_send_disconn_req(chan, ECONNRESET);
		return;
	}

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	l2cap_pass_to_tx(chan, control);

	if (control->final) {
		if (!test_and_clear_bit(CONN_REJ_ACT, &chan->conn_state))
			l2cap_retransmit_all(chan, control);
	} else {
		l2cap_retransmit_all(chan, control);
		l2cap_ertm_send(chan);
		if (chan->tx_state == L2CAP_TX_STATE_WAIT_F)
			set_bit(CONN_REJ_ACT, &chan->conn_state);
	}
}