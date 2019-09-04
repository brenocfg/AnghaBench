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
struct tipc_peer {int is_local; int is_head; int /*<<< orphan*/  is_up; int /*<<< orphan*/  applied; } ;
struct tipc_monitor {int /*<<< orphan*/  list_gen; struct tipc_peer* self; } ;

/* Variables and functions */
 struct tipc_peer* peer_nxt (struct tipc_peer*) ; 

__attribute__((used)) static void mon_assign_roles(struct tipc_monitor *mon, struct tipc_peer *head)
{
	struct tipc_peer *peer = peer_nxt(head);
	struct tipc_peer *self = mon->self;
	int i = 0;

	for (; peer != self; peer = peer_nxt(peer)) {
		peer->is_local = false;

		/* Update domain member */
		if (i++ < head->applied) {
			peer->is_head = false;
			if (head == self)
				peer->is_local = true;
			continue;
		}
		/* Assign next domain head */
		if (!peer->is_up)
			continue;
		if (peer->is_head)
			break;
		head = peer;
		head->is_head = true;
		i = 0;
	}
	mon->list_gen++;
}