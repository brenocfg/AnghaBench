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
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {int /*<<< orphan*/  poll; int /*<<< orphan*/  final; struct sk_buff* txseq; } ;
struct l2cap_chan {int /*<<< orphan*/  retrans_list; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  unacked_frames; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  srej_list; int /*<<< orphan*/  srej_q; int /*<<< orphan*/  expected_tx_seq; int /*<<< orphan*/  buffer_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  CONN_REJ_ACT ; 
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int /*<<< orphan*/  CONN_SREJ_ACT ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  L2CAP_EV_RECV_IFRAME 137 
#define  L2CAP_EV_RECV_REJ 136 
#define  L2CAP_EV_RECV_RNR 135 
#define  L2CAP_EV_RECV_RR 134 
#define  L2CAP_EV_RECV_SREJ 133 
 int /*<<< orphan*/  L2CAP_RX_STATE_SREJ_SENT ; 
#define  L2CAP_TXSEQ_DUPLICATE 132 
#define  L2CAP_TXSEQ_EXPECTED 131 
#define  L2CAP_TXSEQ_INVALID 130 
#define  L2CAP_TXSEQ_INVALID_IGNORE 129 
#define  L2CAP_TXSEQ_UNEXPECTED 128 
 int /*<<< orphan*/  __chan_is_moving (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __next_seq (struct l2cap_chan*,struct sk_buff*) ; 
 int /*<<< orphan*/  __set_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_classify_txseq (struct l2cap_chan*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_handle_rej (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_handle_srej (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_pass_to_tx (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int l2cap_reassemble_sdu (struct l2cap_chan*,struct sk_buff*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_retransmit_all (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_send_ack (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_i_or_rr_or_rnr (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_rr_or_rnr (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_srej (struct l2cap_chan*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_seq_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_rx_state_recv(struct l2cap_chan *chan,
			       struct l2cap_ctrl *control,
			       struct sk_buff *skb, u8 event)
{
	int err = 0;
	bool skb_in_use = false;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	switch (event) {
	case L2CAP_EV_RECV_IFRAME:
		switch (l2cap_classify_txseq(chan, control->txseq)) {
		case L2CAP_TXSEQ_EXPECTED:
			l2cap_pass_to_tx(chan, control);

			if (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) {
				BT_DBG("Busy, discarding expected seq %d",
				       control->txseq);
				break;
			}

			chan->expected_tx_seq = __next_seq(chan,
							   control->txseq);

			chan->buffer_seq = chan->expected_tx_seq;
			skb_in_use = true;

			err = l2cap_reassemble_sdu(chan, skb, control);
			if (err)
				break;

			if (control->final) {
				if (!test_and_clear_bit(CONN_REJ_ACT,
							&chan->conn_state)) {
					control->final = 0;
					l2cap_retransmit_all(chan, control);
					l2cap_ertm_send(chan);
				}
			}

			if (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state))
				l2cap_send_ack(chan);
			break;
		case L2CAP_TXSEQ_UNEXPECTED:
			l2cap_pass_to_tx(chan, control);

			/* Can't issue SREJ frames in the local busy state.
			 * Drop this frame, it will be seen as missing
			 * when local busy is exited.
			 */
			if (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) {
				BT_DBG("Busy, discarding unexpected seq %d",
				       control->txseq);
				break;
			}

			/* There was a gap in the sequence, so an SREJ
			 * must be sent for each missing frame.  The
			 * current frame is stored for later use.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			clear_bit(CONN_SREJ_ACT, &chan->conn_state);
			l2cap_seq_list_clear(&chan->srej_list);
			l2cap_send_srej(chan, control->txseq);

			chan->rx_state = L2CAP_RX_STATE_SREJ_SENT;
			break;
		case L2CAP_TXSEQ_DUPLICATE:
			l2cap_pass_to_tx(chan, control);
			break;
		case L2CAP_TXSEQ_INVALID_IGNORE:
			break;
		case L2CAP_TXSEQ_INVALID:
		default:
			l2cap_send_disconn_req(chan, ECONNRESET);
			break;
		}
		break;
	case L2CAP_EV_RECV_RR:
		l2cap_pass_to_tx(chan, control);
		if (control->final) {
			clear_bit(CONN_REMOTE_BUSY, &chan->conn_state);

			if (!test_and_clear_bit(CONN_REJ_ACT, &chan->conn_state) &&
			    !__chan_is_moving(chan)) {
				control->final = 0;
				l2cap_retransmit_all(chan, control);
			}

			l2cap_ertm_send(chan);
		} else if (control->poll) {
			l2cap_send_i_or_rr_or_rnr(chan);
		} else {
			if (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames)
				__set_retrans_timer(chan);

			l2cap_ertm_send(chan);
		}
		break;
	case L2CAP_EV_RECV_RNR:
		set_bit(CONN_REMOTE_BUSY, &chan->conn_state);
		l2cap_pass_to_tx(chan, control);
		if (control && control->poll) {
			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			l2cap_send_rr_or_rnr(chan, 0);
		}
		__clear_retrans_timer(chan);
		l2cap_seq_list_clear(&chan->retrans_list);
		break;
	case L2CAP_EV_RECV_REJ:
		l2cap_handle_rej(chan, control);
		break;
	case L2CAP_EV_RECV_SREJ:
		l2cap_handle_srej(chan, control);
		break;
	default:
		break;
	}

	if (skb && !skb_in_use) {
		BT_DBG("Freeing %p", skb);
		kfree_skb(skb);
	}

	return err;
}