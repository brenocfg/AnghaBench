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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_peer {int down_cnt; int is_local; int is_head; } ;
struct tipc_monitor {scalar_t__ list_gen; scalar_t__ dom_gen; int /*<<< orphan*/  lock; } ;
struct tipc_mon_state {int probing; int monitoring; scalar_t__ list_gen; scalar_t__ acked_gen; int reset; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int MAX_PEER_DOWN_EVENTS ; 
 struct tipc_peer* get_peer (struct tipc_monitor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_mon_is_active (struct net*,struct tipc_monitor*) ; 
 struct tipc_monitor* tipc_monitor (struct net*,int) ; 

void tipc_mon_get_state(struct net *net, u32 addr,
			struct tipc_mon_state *state,
			int bearer_id)
{
	struct tipc_monitor *mon = tipc_monitor(net, bearer_id);
	struct tipc_peer *peer;

	if (!tipc_mon_is_active(net, mon)) {
		state->probing = false;
		state->monitoring = true;
		return;
	}

	/* Used cached state if table has not changed */
	if (!state->probing &&
	    (state->list_gen == mon->list_gen) &&
	    (state->acked_gen == mon->dom_gen))
		return;

	read_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	if (peer) {
		state->probing = state->acked_gen != mon->dom_gen;
		state->probing |= peer->down_cnt;
		state->reset |= peer->down_cnt >= MAX_PEER_DOWN_EVENTS;
		state->monitoring = peer->is_local;
		state->monitoring |= peer->is_head;
		state->list_gen = mon->list_gen;
	}
	read_unlock_bh(&mon->lock);
}