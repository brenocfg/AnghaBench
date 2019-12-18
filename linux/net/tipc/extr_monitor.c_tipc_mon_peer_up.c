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
struct tipc_peer {int is_up; } ;
struct tipc_monitor {int /*<<< orphan*/  lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_peer* get_peer (struct tipc_monitor*,int /*<<< orphan*/ ) ; 
 struct tipc_peer* get_self (struct net*,int) ; 
 int /*<<< orphan*/  mon_assign_roles (struct tipc_monitor*,struct tipc_peer*) ; 
 int /*<<< orphan*/  mon_update_local_domain (struct tipc_monitor*) ; 
 struct tipc_peer* peer_head (struct tipc_peer*) ; 
 int /*<<< orphan*/  tipc_mon_add_peer (struct tipc_monitor*,int /*<<< orphan*/ ,struct tipc_peer**) ; 
 struct tipc_monitor* tipc_monitor (struct net*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_mon_peer_up(struct net *net, u32 addr, int bearer_id)
{
	struct tipc_monitor *mon = tipc_monitor(net, bearer_id);
	struct tipc_peer *self = get_self(net, bearer_id);
	struct tipc_peer *peer, *head;

	write_lock_bh(&mon->lock);
	peer = get_peer(mon, addr);
	if (!peer && !tipc_mon_add_peer(mon, addr, &peer))
		goto exit;
	peer->is_up = true;
	head = peer_head(peer);
	if (head == self)
		mon_update_local_domain(mon);
	mon_assign_roles(mon, head);
exit:
	write_unlock_bh(&mon->lock);
}