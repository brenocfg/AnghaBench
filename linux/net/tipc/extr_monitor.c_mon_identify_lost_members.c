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
struct tipc_peer {int applied; int down_cnt; scalar_t__ is_local; int /*<<< orphan*/  is_up; struct tipc_mon_domain* domain; } ;
struct tipc_mon_domain {int /*<<< orphan*/  up_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_get (int /*<<< orphan*/ ,int) ; 
 struct tipc_peer* peer_nxt (struct tipc_peer*) ; 

__attribute__((used)) static void mon_identify_lost_members(struct tipc_peer *peer,
				      struct tipc_mon_domain *dom_bef,
				      int applied_bef)
{
	struct tipc_peer *member = peer;
	struct tipc_mon_domain *dom_aft = peer->domain;
	int applied_aft = peer->applied;
	int i;

	for (i = 0; i < applied_bef; i++) {
		member = peer_nxt(member);

		/* Do nothing if self or peer already see member as down */
		if (!member->is_up || !map_get(dom_bef->up_map, i))
			continue;

		/* Loss of local node must be detected by active probing */
		if (member->is_local)
			continue;

		/* Start probing if member was removed from applied domain */
		if (!applied_aft || (applied_aft < i)) {
			member->down_cnt = 1;
			continue;
		}

		/* Member loss is confirmed if it is still in applied domain */
		if (!map_get(dom_aft->up_map, i))
			member->down_cnt++;
	}
}