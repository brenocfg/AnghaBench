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
struct l2cap_ctrl {int sframe; int poll; int /*<<< orphan*/  reqseq; int /*<<< orphan*/  super; } ;
struct l2cap_chan {int /*<<< orphan*/  buffer_seq; int /*<<< orphan*/  conn_state; } ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  L2CAP_SUPER_RNR ; 
 int /*<<< orphan*/  L2CAP_SUPER_RR ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_send_rr_or_rnr(struct l2cap_chan *chan, bool poll)
{
	struct l2cap_ctrl control;

	BT_DBG("chan %p, poll %d", chan, poll);

	memset(&control, 0, sizeof(control));
	control.sframe = 1;
	control.poll = poll;

	if (test_bit(CONN_LOCAL_BUSY, &chan->conn_state))
		control.super = L2CAP_SUPER_RNR;
	else
		control.super = L2CAP_SUPER_RR;

	control.reqseq = chan->buffer_seq;
	l2cap_send_sframe(chan, &control);
}