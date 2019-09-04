#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tb_switch {int authorized; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct tb_port {TYPE_3__* remote; TYPE_1__* sw; scalar_t__ link_nr; scalar_t__ dual_link_port; TYPE_2__ config; } ;
struct TYPE_6__ {struct tb_port* remote; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  tb; } ;

/* Variables and functions */
 scalar_t__ TB_TYPE_PORT ; 
 int /*<<< orphan*/  tb_downstream_route (struct tb_port*) ; 
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 int /*<<< orphan*/  tb_port_WARN (struct tb_port*,char*) ; 
 int /*<<< orphan*/  tb_scan_switch (struct tb_switch*) ; 
 scalar_t__ tb_switch_add (struct tb_switch*) ; 
 struct tb_switch* tb_switch_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tb_switch_configure (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_switch_put (struct tb_switch*) ; 
 TYPE_3__* tb_upstream_port (struct tb_switch*) ; 
 scalar_t__ tb_wait_for_port (struct tb_port*,int) ; 

__attribute__((used)) static void tb_scan_port(struct tb_port *port)
{
	struct tb_switch *sw;
	if (tb_is_upstream_port(port))
		return;
	if (port->config.type != TB_TYPE_PORT)
		return;
	if (port->dual_link_port && port->link_nr)
		return; /*
			 * Downstream switch is reachable through two ports.
			 * Only scan on the primary port (link_nr == 0).
			 */
	if (tb_wait_for_port(port, false) <= 0)
		return;
	if (port->remote) {
		tb_port_WARN(port, "port already has a remote!\n");
		return;
	}
	sw = tb_switch_alloc(port->sw->tb, &port->sw->dev,
			     tb_downstream_route(port));
	if (!sw)
		return;

	if (tb_switch_configure(sw)) {
		tb_switch_put(sw);
		return;
	}

	sw->authorized = true;

	if (tb_switch_add(sw)) {
		tb_switch_put(sw);
		return;
	}

	port->remote = tb_upstream_port(sw);
	tb_upstream_port(sw)->remote = port;
	tb_scan_switch(sw);
}