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
struct l2cap_chan {scalar_t__ local_amp_id; scalar_t__ chan_policy; scalar_t__ move_id; int /*<<< orphan*/  move_state; void* move_role; } ;

/* Variables and functions */
 scalar_t__ AMP_ID_BREDR ; 
 scalar_t__ BT_CHANNEL_POLICY_AMP_PREFERRED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 void* L2CAP_MOVE_ROLE_INITIATOR ; 
 int /*<<< orphan*/  L2CAP_MOVE_WAIT_PREPARE ; 
 int /*<<< orphan*/  L2CAP_MOVE_WAIT_RSP_SUCCESS ; 
 int /*<<< orphan*/  l2cap_move_setup (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_move_chan_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

void l2cap_move_start(struct l2cap_chan *chan)
{
	BT_DBG("chan %p", chan);

	if (chan->local_amp_id == AMP_ID_BREDR) {
		if (chan->chan_policy != BT_CHANNEL_POLICY_AMP_PREFERRED)
			return;
		chan->move_role = L2CAP_MOVE_ROLE_INITIATOR;
		chan->move_state = L2CAP_MOVE_WAIT_PREPARE;
		/* Placeholder - start physical link setup */
	} else {
		chan->move_role = L2CAP_MOVE_ROLE_INITIATOR;
		chan->move_state = L2CAP_MOVE_WAIT_RSP_SUCCESS;
		chan->move_id = 0;
		l2cap_move_setup(chan);
		l2cap_send_move_chan_req(chan, 0);
	}
}