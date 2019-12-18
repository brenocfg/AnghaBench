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
typedef  int /*<<< orphan*/  u16 ;
struct tipc_msg {int dummy; } ;
struct tipc_link {int peer_caps; int /*<<< orphan*/  rcv_nxt_state; int /*<<< orphan*/  in_session; int /*<<< orphan*/  peer_session; } ;

/* Variables and functions */
#define  ACTIVATE_MSG 130 
 scalar_t__ LINK_PROTOCOL ; 
#define  RESET_MSG 129 
#define  STATE_MSG 128 
 int TIPC_LINK_PROTO_SEQNO ; 
 int /*<<< orphan*/  less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_is_up (struct tipc_link*) ; 
 int more (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_ack (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_session (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 

bool tipc_link_validate_msg(struct tipc_link *l, struct tipc_msg *hdr)
{
	u16 curr_session = l->peer_session;
	u16 session = msg_session(hdr);
	int mtyp = msg_type(hdr);

	if (msg_user(hdr) != LINK_PROTOCOL)
		return true;

	switch (mtyp) {
	case RESET_MSG:
		if (!l->in_session)
			return true;
		/* Accept only RESET with new session number */
		return more(session, curr_session);
	case ACTIVATE_MSG:
		if (!l->in_session)
			return true;
		/* Accept only ACTIVATE with new or current session number */
		return !less(session, curr_session);
	case STATE_MSG:
		/* Accept only STATE with current session number */
		if (!l->in_session)
			return false;
		if (session != curr_session)
			return false;
		/* Extra sanity check */
		if (!link_is_up(l) && msg_ack(hdr))
			return false;
		if (!(l->peer_caps & TIPC_LINK_PROTO_SEQNO))
			return true;
		/* Accept only STATE with new sequence number */
		return !less(msg_seqno(hdr), l->rcv_nxt_state);
	default:
		return false;
	}
}