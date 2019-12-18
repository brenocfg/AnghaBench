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
struct tipc_link {int state; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  LINK_ESTABLISHED 142 
#define  LINK_ESTABLISHING 141 
#define  LINK_ESTABLISH_EVT 140 
#define  LINK_FAILINGOVER 139 
#define  LINK_FAILOVER_BEGIN_EVT 138 
#define  LINK_FAILOVER_END_EVT 137 
#define  LINK_FAILURE_EVT 136 
#define  LINK_PEER_RESET 135 
#define  LINK_PEER_RESET_EVT 134 
#define  LINK_RESET 133 
#define  LINK_RESETTING 132 
#define  LINK_RESET_EVT 131 
#define  LINK_SYNCHING 130 
#define  LINK_SYNCH_BEGIN_EVT 129 
#define  LINK_SYNCH_END_EVT 128 
 int TIPC_LINK_DOWN_EVT ; 
 int /*<<< orphan*/  pr_err (char*,int,int,...) ; 
 int /*<<< orphan*/  trace_tipc_link_fsm (int /*<<< orphan*/ ,int,int,int) ; 

int tipc_link_fsm_evt(struct tipc_link *l, int evt)
{
	int rc = 0;
	int old_state = l->state;

	switch (l->state) {
	case LINK_RESETTING:
		switch (evt) {
		case LINK_PEER_RESET_EVT:
			l->state = LINK_PEER_RESET;
			break;
		case LINK_RESET_EVT:
			l->state = LINK_RESET;
			break;
		case LINK_FAILURE_EVT:
		case LINK_FAILOVER_BEGIN_EVT:
		case LINK_ESTABLISH_EVT:
		case LINK_FAILOVER_END_EVT:
		case LINK_SYNCH_BEGIN_EVT:
		case LINK_SYNCH_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_RESET:
		switch (evt) {
		case LINK_PEER_RESET_EVT:
			l->state = LINK_ESTABLISHING;
			break;
		case LINK_FAILOVER_BEGIN_EVT:
			l->state = LINK_FAILINGOVER;
		case LINK_FAILURE_EVT:
		case LINK_RESET_EVT:
		case LINK_ESTABLISH_EVT:
		case LINK_FAILOVER_END_EVT:
			break;
		case LINK_SYNCH_BEGIN_EVT:
		case LINK_SYNCH_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_PEER_RESET:
		switch (evt) {
		case LINK_RESET_EVT:
			l->state = LINK_ESTABLISHING;
			break;
		case LINK_PEER_RESET_EVT:
		case LINK_ESTABLISH_EVT:
		case LINK_FAILURE_EVT:
			break;
		case LINK_SYNCH_BEGIN_EVT:
		case LINK_SYNCH_END_EVT:
		case LINK_FAILOVER_BEGIN_EVT:
		case LINK_FAILOVER_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_FAILINGOVER:
		switch (evt) {
		case LINK_FAILOVER_END_EVT:
			l->state = LINK_RESET;
			break;
		case LINK_PEER_RESET_EVT:
		case LINK_RESET_EVT:
		case LINK_ESTABLISH_EVT:
		case LINK_FAILURE_EVT:
			break;
		case LINK_FAILOVER_BEGIN_EVT:
		case LINK_SYNCH_BEGIN_EVT:
		case LINK_SYNCH_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_ESTABLISHING:
		switch (evt) {
		case LINK_ESTABLISH_EVT:
			l->state = LINK_ESTABLISHED;
			break;
		case LINK_FAILOVER_BEGIN_EVT:
			l->state = LINK_FAILINGOVER;
			break;
		case LINK_RESET_EVT:
			l->state = LINK_RESET;
			break;
		case LINK_FAILURE_EVT:
		case LINK_PEER_RESET_EVT:
		case LINK_SYNCH_BEGIN_EVT:
		case LINK_FAILOVER_END_EVT:
			break;
		case LINK_SYNCH_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_ESTABLISHED:
		switch (evt) {
		case LINK_PEER_RESET_EVT:
			l->state = LINK_PEER_RESET;
			rc |= TIPC_LINK_DOWN_EVT;
			break;
		case LINK_FAILURE_EVT:
			l->state = LINK_RESETTING;
			rc |= TIPC_LINK_DOWN_EVT;
			break;
		case LINK_RESET_EVT:
			l->state = LINK_RESET;
			break;
		case LINK_ESTABLISH_EVT:
		case LINK_SYNCH_END_EVT:
			break;
		case LINK_SYNCH_BEGIN_EVT:
			l->state = LINK_SYNCHING;
			break;
		case LINK_FAILOVER_BEGIN_EVT:
		case LINK_FAILOVER_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	case LINK_SYNCHING:
		switch (evt) {
		case LINK_PEER_RESET_EVT:
			l->state = LINK_PEER_RESET;
			rc |= TIPC_LINK_DOWN_EVT;
			break;
		case LINK_FAILURE_EVT:
			l->state = LINK_RESETTING;
			rc |= TIPC_LINK_DOWN_EVT;
			break;
		case LINK_RESET_EVT:
			l->state = LINK_RESET;
			break;
		case LINK_ESTABLISH_EVT:
		case LINK_SYNCH_BEGIN_EVT:
			break;
		case LINK_SYNCH_END_EVT:
			l->state = LINK_ESTABLISHED;
			break;
		case LINK_FAILOVER_BEGIN_EVT:
		case LINK_FAILOVER_END_EVT:
		default:
			goto illegal_evt;
		}
		break;
	default:
		pr_err("Unknown FSM state %x in %s\n", l->state, l->name);
	}
	trace_tipc_link_fsm(l->name, old_state, l->state, evt);
	return rc;
illegal_evt:
	pr_err("Illegal FSM event %x in state %x on link %s\n",
	       evt, l->state, l->name);
	trace_tipc_link_fsm(l->name, old_state, l->state, evt);
	return rc;
}