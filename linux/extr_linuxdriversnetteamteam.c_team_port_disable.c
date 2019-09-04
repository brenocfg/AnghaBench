#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct team_port {int index; int /*<<< orphan*/  hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_disabled ) (struct team*,struct team_port*) ;} ;
struct team {int /*<<< orphan*/  en_port_count; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reconstruct_port_hlist (struct team*,int) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct team*,struct team_port*) ; 
 int /*<<< orphan*/  team_adjust_ops (struct team*) ; 
 int /*<<< orphan*/  team_lower_state_changed (struct team_port*) ; 
 int /*<<< orphan*/  team_port_enabled (struct team_port*) ; 
 int /*<<< orphan*/  team_queue_override_port_del (struct team*,struct team_port*) ; 

__attribute__((used)) static void team_port_disable(struct team *team,
			      struct team_port *port)
{
	if (!team_port_enabled(port))
		return;
	if (team->ops.port_disabled)
		team->ops.port_disabled(team, port);
	hlist_del_rcu(&port->hlist);
	__reconstruct_port_hlist(team, port->index);
	port->index = -1;
	team->en_port_count--;
	team_queue_override_port_del(team, port);
	team_adjust_ops(team);
	team_lower_state_changed(port);
}