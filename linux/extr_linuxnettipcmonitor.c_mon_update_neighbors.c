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
struct tipc_peer {int dummy; } ;
struct tipc_monitor {int /*<<< orphan*/  peer_cnt; } ;

/* Variables and functions */
 int dom_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_apply_domain (struct tipc_monitor*,struct tipc_peer*) ; 
 struct tipc_peer* peer_prev (struct tipc_peer*) ; 

__attribute__((used)) static void mon_update_neighbors(struct tipc_monitor *mon,
				 struct tipc_peer *peer)
{
	int dz, i;

	dz = dom_size(mon->peer_cnt);
	for (i = 0; i < dz; i++) {
		mon_apply_domain(mon, peer);
		peer = peer_prev(peer);
	}
}