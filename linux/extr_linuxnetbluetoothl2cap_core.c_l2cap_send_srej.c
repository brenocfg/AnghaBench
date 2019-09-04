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
typedef  scalar_t__ u16 ;
struct l2cap_ctrl {int sframe; scalar_t__ reqseq; int /*<<< orphan*/  super; } ;
struct l2cap_chan {scalar_t__ expected_tx_seq; int /*<<< orphan*/  srej_list; int /*<<< orphan*/  srej_q; } ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_SUPER_SREJ ; 
 scalar_t__ __next_seq (struct l2cap_chan*,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_ertm_seq_in_queue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_seq_list_append (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l2cap_send_srej(struct l2cap_chan *chan, u16 txseq)
{
	struct l2cap_ctrl control;
	u16 seq;

	BT_DBG("chan %p, txseq %u", chan, txseq);

	memset(&control, 0, sizeof(control));
	control.sframe = 1;
	control.super = L2CAP_SUPER_SREJ;

	for (seq = chan->expected_tx_seq; seq != txseq;
	     seq = __next_seq(chan, seq)) {
		if (!l2cap_ertm_seq_in_queue(&chan->srej_q, seq)) {
			control.reqseq = seq;
			l2cap_send_sframe(chan, &control);
			l2cap_seq_list_append(&chan->srej_list, seq);
		}
	}

	chan->expected_tx_seq = __next_seq(chan, txseq);
}