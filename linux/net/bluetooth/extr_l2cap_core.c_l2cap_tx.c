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
struct sk_buff_head {int dummy; } ;
struct l2cap_ctrl {int dummy; } ;
struct l2cap_chan {int tx_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff_head*,int /*<<< orphan*/ ,int) ; 
#define  L2CAP_TX_STATE_WAIT_F 129 
#define  L2CAP_TX_STATE_XMIT 128 
 int /*<<< orphan*/  l2cap_tx_state_wait_f (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_tx_state_xmit (struct l2cap_chan*,struct l2cap_ctrl*,struct sk_buff_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_tx(struct l2cap_chan *chan, struct l2cap_ctrl *control,
		     struct sk_buff_head *skbs, u8 event)
{
	BT_DBG("chan %p, control %p, skbs %p, event %d, state %d",
	       chan, control, skbs, event, chan->tx_state);

	switch (chan->tx_state) {
	case L2CAP_TX_STATE_XMIT:
		l2cap_tx_state_xmit(chan, control, skbs, event);
		break;
	case L2CAP_TX_STATE_WAIT_F:
		l2cap_tx_state_wait_f(chan, control, skbs, event);
		break;
	default:
		/* Ignore event */
		break;
	}
}