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
struct sk_buff_head {int dummy; } ;
struct l2cap_ctrl {int sframe; int poll; int /*<<< orphan*/  final; int /*<<< orphan*/  reqseq; int /*<<< orphan*/  super; } ;
struct l2cap_chan {int retry_count; int max_tx; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  unacked_frames; int /*<<< orphan*/  buffer_seq; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  tx_q; int /*<<< orphan*/ * tx_send_head; } ;
typedef  int /*<<< orphan*/  local_control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  CONN_RNR_SENT ; 
 int /*<<< orphan*/  ECONNABORTED ; 
#define  L2CAP_EV_DATA_REQUEST 134 
#define  L2CAP_EV_EXPLICIT_POLL 133 
#define  L2CAP_EV_LOCAL_BUSY_CLEAR 132 
#define  L2CAP_EV_LOCAL_BUSY_DETECTED 131 
#define  L2CAP_EV_MONITOR_TO 130 
#define  L2CAP_EV_RECV_FBIT 129 
#define  L2CAP_EV_RECV_REQSEQ_AND_FBIT 128 
 int /*<<< orphan*/  L2CAP_RX_STATE_SREJ_SENT ; 
 int /*<<< orphan*/  L2CAP_SUPER_RR ; 
 int /*<<< orphan*/  L2CAP_TX_STATE_WAIT_F ; 
 int /*<<< orphan*/  L2CAP_TX_STATE_XMIT ; 
 int /*<<< orphan*/  __clear_monitor_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __set_monitor_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __set_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_abort_rx_srej_sent (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_process_reqseq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_ack (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_rr_or_rnr (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_peek (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_tx_state_wait_f(struct l2cap_chan *chan,
				  struct l2cap_ctrl *control,
				  struct sk_buff_head *skbs, u8 event)
{
	BT_DBG("chan %p, control %p, skbs %p, event %d", chan, control, skbs,
	       event);

	switch (event) {
	case L2CAP_EV_DATA_REQUEST:
		if (chan->tx_send_head == NULL)
			chan->tx_send_head = skb_peek(skbs);
		/* Queue data, but don't send. */
		skb_queue_splice_tail_init(skbs, &chan->tx_q);
		break;
	case L2CAP_EV_LOCAL_BUSY_DETECTED:
		BT_DBG("Enter LOCAL_BUSY");
		set_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		if (chan->rx_state == L2CAP_RX_STATE_SREJ_SENT) {
			/* The SREJ_SENT state must be aborted if we are to
			 * enter the LOCAL_BUSY state.
			 */
			l2cap_abort_rx_srej_sent(chan);
		}

		l2cap_send_ack(chan);

		break;
	case L2CAP_EV_LOCAL_BUSY_CLEAR:
		BT_DBG("Exit LOCAL_BUSY");
		clear_bit(CONN_LOCAL_BUSY, &chan->conn_state);

		if (test_bit(CONN_RNR_SENT, &chan->conn_state)) {
			struct l2cap_ctrl local_control;
			memset(&local_control, 0, sizeof(local_control));
			local_control.sframe = 1;
			local_control.super = L2CAP_SUPER_RR;
			local_control.poll = 1;
			local_control.reqseq = chan->buffer_seq;
			l2cap_send_sframe(chan, &local_control);

			chan->retry_count = 1;
			__set_monitor_timer(chan);
			chan->tx_state = L2CAP_TX_STATE_WAIT_F;
		}
		break;
	case L2CAP_EV_RECV_REQSEQ_AND_FBIT:
		l2cap_process_reqseq(chan, control->reqseq);

		/* Fall through */

	case L2CAP_EV_RECV_FBIT:
		if (control && control->final) {
			__clear_monitor_timer(chan);
			if (chan->unacked_frames > 0)
				__set_retrans_timer(chan);
			chan->retry_count = 0;
			chan->tx_state = L2CAP_TX_STATE_XMIT;
			BT_DBG("recv fbit tx_state 0x2.2%x", chan->tx_state);
		}
		break;
	case L2CAP_EV_EXPLICIT_POLL:
		/* Ignore */
		break;
	case L2CAP_EV_MONITOR_TO:
		if (chan->max_tx == 0 || chan->retry_count < chan->max_tx) {
			l2cap_send_rr_or_rnr(chan, 1);
			__set_monitor_timer(chan);
			chan->retry_count++;
		} else {
			l2cap_send_disconn_req(chan, ECONNABORTED);
		}
		break;
	default:
		break;
	}
}