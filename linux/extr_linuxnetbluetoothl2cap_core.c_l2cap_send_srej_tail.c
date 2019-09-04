#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct l2cap_ctrl {int sframe; scalar_t__ reqseq; int /*<<< orphan*/  super; } ;
struct TYPE_2__ {scalar_t__ tail; } ;
struct l2cap_chan {TYPE_1__ srej_list; } ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 scalar_t__ L2CAP_SEQ_LIST_CLEAR ; 
 int /*<<< orphan*/  L2CAP_SUPER_SREJ ; 
 int /*<<< orphan*/  l2cap_send_sframe (struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  memset (struct l2cap_ctrl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void l2cap_send_srej_tail(struct l2cap_chan *chan)
{
	struct l2cap_ctrl control;

	BT_DBG("chan %p", chan);

	if (chan->srej_list.tail == L2CAP_SEQ_LIST_CLEAR)
		return;

	memset(&control, 0, sizeof(control));
	control.sframe = 1;
	control.super = L2CAP_SUPER_SREJ;
	control.reqseq = chan->srej_list.tail;
	l2cap_send_sframe(chan, &control);
}