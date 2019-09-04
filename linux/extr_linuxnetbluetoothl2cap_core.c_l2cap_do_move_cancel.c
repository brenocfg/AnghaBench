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
struct l2cap_chan {scalar_t__ move_role; int /*<<< orphan*/  move_state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ L2CAP_MOVE_ROLE_NONE ; 
 scalar_t__ L2CAP_MOVE_ROLE_RESPONDER ; 
 int /*<<< orphan*/  L2CAP_MOVE_STABLE ; 
 int /*<<< orphan*/  L2CAP_MR_BAD_ID ; 
 int /*<<< orphan*/  L2CAP_MR_NOT_ALLOWED ; 
 int /*<<< orphan*/  l2cap_ertm_send (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_move_chan_rsp (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_do_move_cancel(struct l2cap_chan *chan, int result)
{
	if (chan->move_role == L2CAP_MOVE_ROLE_RESPONDER) {
		u8 rsp_result;
		if (result == -EINVAL)
			rsp_result = L2CAP_MR_BAD_ID;
		else
			rsp_result = L2CAP_MR_NOT_ALLOWED;

		l2cap_send_move_chan_rsp(chan, rsp_result);
	}

	chan->move_role = L2CAP_MOVE_ROLE_NONE;
	chan->move_state = L2CAP_MOVE_STABLE;

	/* Restart data transmission */
	l2cap_ertm_send(chan);
}