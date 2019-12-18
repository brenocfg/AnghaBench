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
struct l2cap_ctrl {int /*<<< orphan*/  reqseq; } ;
struct l2cap_chan {int rx_state; int /*<<< orphan*/  expected_ack_seq; int /*<<< orphan*/  next_tx_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_ctrl*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ECONNRESET ; 
#define  L2CAP_RX_STATE_RECV 131 
#define  L2CAP_RX_STATE_SREJ_SENT 130 
#define  L2CAP_RX_STATE_WAIT_F 129 
#define  L2CAP_RX_STATE_WAIT_P 128 
 scalar_t__ __valid_reqseq (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int l2cap_rx_state_recv (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int l2cap_rx_state_srej_sent (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int l2cap_rx_state_wait_f (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int l2cap_rx_state_wait_p (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_rx(struct l2cap_chan *chan, struct l2cap_ctrl *control,
		    struct sk_buff *skb, u8 event)
{
	int err = 0;

	BT_DBG("chan %p, control %p, skb %p, event %d, state %d", chan,
	       control, skb, event, chan->rx_state);

	if (__valid_reqseq(chan, control->reqseq)) {
		switch (chan->rx_state) {
		case L2CAP_RX_STATE_RECV:
			err = l2cap_rx_state_recv(chan, control, skb, event);
			break;
		case L2CAP_RX_STATE_SREJ_SENT:
			err = l2cap_rx_state_srej_sent(chan, control, skb,
						       event);
			break;
		case L2CAP_RX_STATE_WAIT_P:
			err = l2cap_rx_state_wait_p(chan, control, skb, event);
			break;
		case L2CAP_RX_STATE_WAIT_F:
			err = l2cap_rx_state_wait_f(chan, control, skb, event);
			break;
		default:
			/* shut it down */
			break;
		}
	} else {
		BT_DBG("Invalid reqseq %d (next_tx_seq %d, expected_ack_seq %d",
		       control->reqseq, chan->next_tx_seq,
		       chan->expected_ack_seq);
		l2cap_send_disconn_req(chan, ECONNRESET);
	}

	return err;
}