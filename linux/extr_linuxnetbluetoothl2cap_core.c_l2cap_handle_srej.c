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
struct l2cap_ctrl {int /*<<< orphan*/  reqseq; scalar_t__ final; scalar_t__ poll; } ;
struct l2cap_chan {scalar_t__ tx_state; int /*<<< orphan*/  srej_save_reqseq; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  next_tx_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  retries; } ;
struct TYPE_4__ {TYPE_1__ l2cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int /*<<< orphan*/  CONN_SREJ_ACT ; 
 int /*<<< orphan*/  ECONNRESET ; 
 scalar_t__ L2CAP_TX_STATE_WAIT_F ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 struct sk_buff* l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_pass_to_tx (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_pass_to_tx_fbit (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_retransmit (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_handle_srej(struct l2cap_chan *chan,
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

	if (skb == NULL) {
		BT_DBG("Seq %d not available for retransmission",
		       control->reqseq);
		return;
	}

	if (chan->max_tx != 0 && bt_cb(skb)->l2cap.retries >= chan->max_tx) {
		BT_DBG("Retry limit exceeded (%d)", chan->max_tx);
		l2cap_send_disconn_req(chan, ECONNRESET);
		return;
	}

	clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

	if (control->poll) {
		l2cap_pass_to_tx(chan, control);

		set_bit(CONN_SEND_FBIT, &chan->conn_state);
		l2cap_retransmit(chan, control);
		l2cap_ertm_send(chan);

		if (chan->tx_state == L2CAP_TX_STATE_WAIT_F) {
			set_bit(CONN_SREJ_ACT, &chan->conn_state);
			chan->srej_save_reqseq = control->reqseq;
		}
	} else {
		l2cap_pass_to_tx_fbit(chan, control);

		if (control->final) {
			if (chan->srej_save_reqseq != control->reqseq ||
			    !test_and_clear_bit(CONN_SREJ_ACT,
						&chan->conn_state))
				l2cap_retransmit(chan, control);
		} else {
			l2cap_retransmit(chan, control);
			if (chan->tx_state == L2CAP_TX_STATE_WAIT_F) {
				set_bit(CONN_SREJ_ACT, &chan->conn_state);
				chan->srej_save_reqseq = control->reqseq;
			}
		}
	}
}