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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct l2cap_ctrl {int final; scalar_t__ super; int /*<<< orphan*/  poll; int /*<<< orphan*/  reqseq; int /*<<< orphan*/  sframe; } ;
struct l2cap_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/  last_acked_seq; int /*<<< orphan*/  conn_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,...) ; 
 int /*<<< orphan*/  CONN_RNR_SENT ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int /*<<< orphan*/  FLAG_EXT_CTRL ; 
 int /*<<< orphan*/  IS_ERR (struct sk_buff*) ; 
 scalar_t__ L2CAP_SUPER_RNR ; 
 scalar_t__ L2CAP_SUPER_RR ; 
 scalar_t__ L2CAP_SUPER_SREJ ; 
 scalar_t__ __chan_is_moving (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_ack_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __pack_enhanced_control (struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  __pack_extended_control (struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* l2cap_create_sframe_pdu (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_do_send (struct l2cap_chan*,struct sk_buff*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_send_sframe(struct l2cap_chan *chan,
			      struct l2cap_ctrl *control)
{
	struct sk_buff *skb;
	u32 control_field;

	BT_DBG("chan %p, control %p", chan, control);

	if (!control->sframe)
		return;

	if (__chan_is_moving(chan))
		return;

	if (test_and_clear_bit(CONN_SEND_FBIT, &chan->conn_state) &&
	    !control->poll)
		control->final = 1;

	if (control->super == L2CAP_SUPER_RR)
		clear_bit(CONN_RNR_SENT, &chan->conn_state);
	else if (control->super == L2CAP_SUPER_RNR)
		set_bit(CONN_RNR_SENT, &chan->conn_state);

	if (control->super != L2CAP_SUPER_SREJ) {
		chan->last_acked_seq = control->reqseq;
		__clear_ack_timer(chan);
	}

	BT_DBG("reqseq %d, final %d, poll %d, super %d", control->reqseq,
	       control->final, control->poll, control->super);

	if (test_bit(FLAG_EXT_CTRL, &chan->flags))
		control_field = __pack_extended_control(control);
	else
		control_field = __pack_enhanced_control(control);

	skb = l2cap_create_sframe_pdu(chan, control_field);
	if (!IS_ERR(skb))
		l2cap_do_send(chan, skb);
}