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
struct l2cap_chan {scalar_t__ state; int move_role; int /*<<< orphan*/  move_state; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int /*<<< orphan*/  L2CAP_MC_UNCONFIRMED ; 
#define  L2CAP_MOVE_ROLE_INITIATOR 129 
#define  L2CAP_MOVE_ROLE_RESPONDER 128 
 int /*<<< orphan*/  L2CAP_MOVE_WAIT_LOGICAL_CFM ; 
 int /*<<< orphan*/  L2CAP_MOVE_WAIT_LOGICAL_COMP ; 
 int /*<<< orphan*/  L2CAP_MR_NOT_SUPP ; 
 int /*<<< orphan*/  l2cap_move_done (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_move_chan_cfm (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_send_move_chan_rsp (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_logical_fail(struct l2cap_chan *chan)
{
	/* Logical link setup failed */
	if (chan->state != BT_CONNECTED) {
		/* Create channel failure, disconnect */
		l2cap_send_disconn_req(chan, ECONNRESET);
		return;
	}

	switch (chan->move_role) {
	case L2CAP_MOVE_ROLE_RESPONDER:
		l2cap_move_done(chan);
		l2cap_send_move_chan_rsp(chan, L2CAP_MR_NOT_SUPP);
		break;
	case L2CAP_MOVE_ROLE_INITIATOR:
		if (chan->move_state == L2CAP_MOVE_WAIT_LOGICAL_COMP ||
		    chan->move_state == L2CAP_MOVE_WAIT_LOGICAL_CFM) {
			/* Remote has only sent pending or
			 * success responses, clean up
			 */
			l2cap_move_done(chan);
		}

		/* Other amp move states imply that the move
		 * has already aborted
		 */
		l2cap_send_move_chan_cfm(chan, L2CAP_MC_UNCONFIRMED);
		break;
	}
}