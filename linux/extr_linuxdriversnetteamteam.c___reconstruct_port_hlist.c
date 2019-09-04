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
struct team_port {int /*<<< orphan*/  index; int /*<<< orphan*/  hlist; } ;
struct team {int en_port_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct team_port* team_get_port_by_index (struct team*,int) ; 
 int /*<<< orphan*/  team_port_index_hash (struct team*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __reconstruct_port_hlist(struct team *team, int rm_index)
{
	int i;
	struct team_port *port;

	for (i = rm_index + 1; i < team->en_port_count; i++) {
		port = team_get_port_by_index(team, i);
		hlist_del_rcu(&port->hlist);
		port->index--;
		hlist_add_head_rcu(&port->hlist,
				   team_port_index_hash(team, port->index));
	}
}