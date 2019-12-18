#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct tipc_mon_state {int probing; int /*<<< orphan*/  monitoring; int /*<<< orphan*/  reset; } ;
struct tipc_link {int state; int silent_intv_cnt; int abort_limit; int rcv_unacked; int rst_cnt; int /*<<< orphan*/  deferdq; int /*<<< orphan*/  transmq; TYPE_2__* bc_rcvlink; int /*<<< orphan*/  bearer_id; int /*<<< orphan*/  addr; int /*<<< orphan*/  net; struct tipc_mon_state mon_state; TYPE_1__* bc_sndlink; } ;
struct sk_buff_head {int dummy; } ;
struct TYPE_4__ {int rcv_unacked; scalar_t__ acked; } ;
struct TYPE_3__ {scalar_t__ snd_nxt; } ;

/* Variables and functions */
 int ACTIVATE_MSG ; 
#define  LINK_ESTABLISHED 134 
#define  LINK_ESTABLISHING 133 
#define  LINK_FAILINGOVER 132 
 int /*<<< orphan*/  LINK_FAILURE_EVT ; 
#define  LINK_PEER_RESET 131 
#define  LINK_RESET 130 
#define  LINK_RESETTING 129 
#define  LINK_SYNCHING 128 
 int RESET_MSG ; 
 int STATE_MSG ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  TIPC_DUMP_NONE ; 
 int /*<<< orphan*/  link_profile_stats (struct tipc_link*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_link_build_proto_msg (struct tipc_link*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_mon_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_mon_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_tipc_link_timeout (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace_tipc_link_too_silent (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 

int tipc_link_timeout(struct tipc_link *l, struct sk_buff_head *xmitq)
{
	int mtyp = 0;
	int rc = 0;
	bool state = false;
	bool probe = false;
	bool setup = false;
	u16 bc_snt = l->bc_sndlink->snd_nxt - 1;
	u16 bc_acked = l->bc_rcvlink->acked;
	struct tipc_mon_state *mstate = &l->mon_state;

	trace_tipc_link_timeout(l, TIPC_DUMP_NONE, " ");
	trace_tipc_link_too_silent(l, TIPC_DUMP_ALL, " ");
	switch (l->state) {
	case LINK_ESTABLISHED:
	case LINK_SYNCHING:
		mtyp = STATE_MSG;
		link_profile_stats(l);
		tipc_mon_get_state(l->net, l->addr, mstate, l->bearer_id);
		if (mstate->reset || (l->silent_intv_cnt > l->abort_limit))
			return tipc_link_fsm_evt(l, LINK_FAILURE_EVT);
		state = bc_acked != bc_snt;
		state |= l->bc_rcvlink->rcv_unacked;
		state |= l->rcv_unacked;
		state |= !skb_queue_empty(&l->transmq);
		state |= !skb_queue_empty(&l->deferdq);
		probe = mstate->probing;
		probe |= l->silent_intv_cnt;
		if (probe || mstate->monitoring)
			l->silent_intv_cnt++;
		break;
	case LINK_RESET:
		setup = l->rst_cnt++ <= 4;
		setup |= !(l->rst_cnt % 16);
		mtyp = RESET_MSG;
		break;
	case LINK_ESTABLISHING:
		setup = true;
		mtyp = ACTIVATE_MSG;
		break;
	case LINK_PEER_RESET:
	case LINK_RESETTING:
	case LINK_FAILINGOVER:
		break;
	default:
		break;
	}

	if (state || probe || setup)
		tipc_link_build_proto_msg(l, mtyp, probe, 0, 0, 0, 0, xmitq);

	return rc;
}