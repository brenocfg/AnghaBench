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
struct l2cap_ctrl {int sframe; int final; int /*<<< orphan*/  super; int /*<<< orphan*/  reqseq; } ;
struct l2cap_chan {scalar_t__ unacked_frames; int /*<<< orphan*/  conn_state; int /*<<< orphan*/  buffer_seq; } ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  CONN_REMOTE_BUSY ; 
 int /*<<< orphan*/  CONN_SEND_FBIT ; 
 int /*<<< orphan*/  L2CAP_SUPER_RNR ; 
 int /*<<< orphan*/  L2CAP_SUPER_RR ; 
 int /*<<< orphan*/  __set_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_send_i_or_rr_or_rnr(struct l2cap_chan *chan)
{
	struct l2cap_ctrl control;

	BT_DBG("chan %p", chan);

	memset(&control, 0, sizeof(control));
	control.sframe = 1;
	control.final = 1;
	control.reqseq = chan->buffer_seq;
	set_bit(CONN_SEND_FBIT, &chan->conn_state);

	if (test_bit(CONN_LOCAL_BUSY, &chan->conn_state)) {
		control.super = L2CAP_SUPER_RNR;
		l2cap_send_sframe(chan, &control);
	}

	if (test_and_clear_bit(CONN_REMOTE_BUSY, &chan->conn_state) &&
	    chan->unacked_frames > 0)
		__set_retrans_timer(chan);

	/* Send pending iframes */
	l2cap_ertm_send(chan);

	if (!test_bit(CONN_LOCAL_BUSY, &chan->conn_state) &&
	    test_bit(CONN_SEND_FBIT, &chan->conn_state)) {
		/* F-bit wasn't sent in an s-frame or i-frame yet, so
		 * send it now.
		 */
		control.super = L2CAP_SUPER_RR;
		l2cap_send_sframe(chan, &control);
	}
}