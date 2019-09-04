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
struct l2cap_ctrl {int /*<<< orphan*/  reqseq; } ;
struct l2cap_chan {int /*<<< orphan*/  retrans_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_ctrl*) ; 
 int /*<<< orphan*/  l2cap_ertm_resend (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_seq_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_retransmit(struct l2cap_chan *chan,
			     struct l2cap_ctrl *control)
{
	BT_DBG("chan %p, control %p", chan, control);

	l2cap_seq_list_append(&chan->retrans_list, control->reqseq);
	l2cap_ertm_resend(chan);
}