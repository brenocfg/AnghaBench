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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {int sframe; int /*<<< orphan*/  reqseq; int /*<<< orphan*/  super; int /*<<< orphan*/  poll; int /*<<< orphan*/  final; int /*<<< orphan*/  txseq; } ;
struct l2cap_chan {int /*<<< orphan*/  buffer_seq; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  unacked_frames; int /*<<< orphan*/  srej_q; int /*<<< orphan*/  srej_list; int /*<<< orphan*/  expected_tx_seq; } ;
typedef  int /*<<< orphan*/  rr_control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  CONN_REJ_ACT ; 
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  L2CAP_EV_RECV_IFRAME 140 
#define  L2CAP_EV_RECV_REJ 139 
#define  L2CAP_EV_RECV_RNR 138 
#define  L2CAP_EV_RECV_RR 137 
#define  L2CAP_EV_RECV_SREJ 136 
 int /*<<< orphan*/  L2CAP_SUPER_RR ; 
#define  L2CAP_TXSEQ_DUPLICATE 135 
#define  L2CAP_TXSEQ_DUPLICATE_SREJ 134 
#define  L2CAP_TXSEQ_EXPECTED 133 
#define  L2CAP_TXSEQ_EXPECTED_SREJ 132 
#define  L2CAP_TXSEQ_INVALID 131 
#define  L2CAP_TXSEQ_INVALID_IGNORE 130 
#define  L2CAP_TXSEQ_UNEXPECTED 129 
#define  L2CAP_TXSEQ_UNEXPECTED_SREJ 128 
 int /*<<< orphan*/  __next_seq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_classify_txseq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_handle_rej (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_handle_srej (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_pass_to_tx (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_retransmit_all (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int l2cap_rx_queued_iframes (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_ack (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_send_srej (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_srej_list (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_srej_tail (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_seq_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_rx_state_srej_sent(struct l2cap_chan *chan,
				    struct l2cap_ctrl *control,
				    struct sk_buff *skb, u8 event)
{
	int err = 0;
	u16 txseq = control->txseq;
	bool skb_in_use = false;

	BT_DBG("chan %p, control %p, skb %p, event %d", chan, control, skb,
	       event);

	switch (event) {
	case L2CAP_EV_RECV_IFRAME:
		switch (l2cap_classify_txseq(chan, txseq)) {
		case L2CAP_TXSEQ_EXPECTED:
			/* Keep frame for reassembly later */
			l2cap_pass_to_tx(chan, control);
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			chan->expected_tx_seq = __next_seq(chan, txseq);
			break;
		case L2CAP_TXSEQ_EXPECTED_SREJ:
			l2cap_seq_list_pop(&chan->srej_list);

			l2cap_pass_to_tx(chan, control);
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			err = l2cap_rx_queued_iframes(chan);
			if (err)
				break;

			break;
		case L2CAP_TXSEQ_UNEXPECTED:
			/* Got a frame that can't be reassembled yet.
			 * Save it for later, and send SREJs to cover
			 * the missing frames.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			l2cap_pass_to_tx(chan, control);
			l2cap_send_srej(chan, control->txseq);
			break;
		case L2CAP_TXSEQ_UNEXPECTED_SREJ:
			/* This frame was requested with an SREJ, but
			 * some expected retransmitted frames are
			 * missing.  Request retransmission of missing
			 * SREJ'd frames.
			 */
			skb_queue_tail(&chan->srej_q, skb);
			skb_in_use = true;
			BT_DBG("Queued %p (queue len %d)", skb,
			       skb_queue_len(&chan->srej_q));

			l2cap_pass_to_tx(chan, control);
			l2cap_send_srej_list(chan, control->txseq);
			break;
		case L2CAP_TXSEQ_DUPLICATE_SREJ:
			/* We've already queued this frame.  Drop this copy. */
			l2cap_pass_to_tx(chan, control);
			break;
		case L2CAP_TXSEQ_DUPLICATE:
			/* Expecting a later sequence number, so this frame
			 * was already received.  Ignore it completely.
			 */
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

			if (!test_and_clear_bit(CONN_REJ_ACT,
						&chan->conn_state)) {
				control->final = 0;
				l2cap_retransmit_all(chan, control);
			}

			l2cap_ertm_send(chan);
		} else if (control->poll) {
			if (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames) {
				__set_retrans_timer(chan);
			}

			set_bit(CONN_SEND_FBIT, &chan->conn_state);
			l2cap_send_srej_tail(chan);
		} else {
			if (test_and_clear_bit(CONN_REMOTE_BUSY,
					       &chan->conn_state) &&
			    chan->unacked_frames)
				__set_retrans_timer(chan);

			l2cap_send_ack(chan);
		}
		break;
	case L2CAP_EV_RECV_RNR:
		set_bit(CONN_REMOTE_BUSY, &chan->conn_state);
		l2cap_pass_to_tx(chan, control);
		if (control->poll) {
			l2cap_send_srej_tail(chan);
		} else {
			struct l2cap_ctrl rr_control;
			memset(&rr_control, 0, sizeof(rr_control));
			rr_control.sframe = 1;
			rr_control.super = L2CAP_SUPER_RR;
			rr_control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &rr_control);
		}

		break;
	case L2CAP_EV_RECV_REJ:
		l2cap_handle_rej(chan, control);
		break;
	case L2CAP_EV_RECV_SREJ:
		l2cap_handle_srej(chan, control);
		break;
	}

	if (skb && !skb_in_use) {
		BT_DBG("Freeing %p", skb);
		kfree_skb(skb);
	}

	return err;
}