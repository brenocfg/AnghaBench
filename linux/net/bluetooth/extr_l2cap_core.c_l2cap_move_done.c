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
struct l2cap_chan {int move_role; scalar_t__ mode; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  move_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  L2CAP_EV_EXPLICIT_POLL ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
#define  L2CAP_MOVE_ROLE_INITIATOR 129 
 int L2CAP_MOVE_ROLE_NONE ; 
#define  L2CAP_MOVE_ROLE_RESPONDER 128 
 int /*<<< orphan*/  L2CAP_MOVE_STABLE ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_WAIT_F ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_WAIT_P ; 
 int /*<<< orphan*/  l2cap_tx (struct l2cap_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_move_done(struct l2cap_chan *chan)
{
	u8 move_role = chan->move_role;
	BT_DBG("chan %p", chan);

	chan->move_state = L2CAP_MOVE_STABLE;
	chan->move_role = L2CAP_MOVE_ROLE_NONE;

	if (chan->mode != L2CAP_MODE_ERTM)
		return;

	switch (move_role) {
	case L2CAP_MOVE_ROLE_INITIATOR:
		l2cap_tx(chan, NULL, NULL, L2CAP_EV_EXPLICIT_POLL);
		chan->rx_state = L2CAP_RX_STATE_WAIT_F;
		break;
	case L2CAP_MOVE_ROLE_RESPONDER:
		chan->rx_state = L2CAP_RX_STATE_WAIT_P;
		break;
	}
}