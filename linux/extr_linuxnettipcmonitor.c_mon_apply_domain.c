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
typedef  scalar_t__ u32 ;
struct tipc_peer {scalar_t__ addr; scalar_t__ applied; int /*<<< orphan*/  is_up; struct tipc_mon_domain* domain; } ;
struct tipc_monitor {int dummy; } ;
struct tipc_mon_domain {int member_cnt; scalar_t__* members; } ;

/* Variables and functions */
 struct tipc_peer* peer_nxt (struct tipc_peer*) ; 

__attribute__((used)) static void mon_apply_domain(struct tipc_monitor *mon,
			     struct tipc_peer *peer)
{
	struct tipc_mon_domain *dom = peer->domain;
	struct tipc_peer *member;
	u32 addr;
	int i;

	if (!dom || !peer->is_up)
		return;

	/* Scan across domain members and match against monitor list */
	peer->applied = 0;
	member = peer_nxt(peer);
	for (i = 0; i < dom->member_cnt; i++) {
		addr = dom->members[i];
		if (addr != member->addr)
			return;
		peer->applied++;
		member = peer_nxt(member);
	}
}