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
struct net_bridge_port {int /*<<< orphan*/  port_id; int /*<<< orphan*/  designated_port; int /*<<< orphan*/  designated_bridge; int /*<<< orphan*/  designated_cost; int /*<<< orphan*/  designated_root; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  bridge_id; int /*<<< orphan*/  root_path_cost; int /*<<< orphan*/  designated_root; } ;

/* Variables and functions */

void br_become_designated_port(struct net_bridge_port *p)
{
	struct net_bridge *br;

	br = p->br;
	p->designated_root = br->designated_root;
	p->designated_cost = br->root_path_cost;
	p->designated_bridge = br->bridge_id;
	p->designated_port = p->port_id;
}