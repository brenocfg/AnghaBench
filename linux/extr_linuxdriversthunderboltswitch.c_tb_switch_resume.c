#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int max_port_number; } ;
struct tb_switch {scalar_t__ uid; struct tb_port* ports; TYPE_1__ config; } ;
struct tb_port {TYPE_2__* remote; } ;
struct TYPE_4__ {struct tb_switch* sw; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int tb_drom_read_uid_only (struct tb_switch*,scalar_t__*) ; 
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 int tb_plug_events_active (struct tb_switch*,int) ; 
 int /*<<< orphan*/  tb_port_warn (struct tb_port*,char*) ; 
 scalar_t__ tb_route (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_info (struct tb_switch*,char*,...) ; 
 int /*<<< orphan*/  tb_sw_set_unplugged (struct tb_switch*) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*) ; 
 int tb_sw_write (struct tb_switch*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ tb_wait_for_port (struct tb_port*,int) ; 

int tb_switch_resume(struct tb_switch *sw)
{
	int i, err;
	tb_sw_info(sw, "resuming switch\n");

	/*
	 * Check for UID of the connected switches except for root
	 * switch which we assume cannot be removed.
	 */
	if (tb_route(sw)) {
		u64 uid;

		err = tb_drom_read_uid_only(sw, &uid);
		if (err) {
			tb_sw_warn(sw, "uid read failed\n");
			return err;
		}
		if (sw->uid != uid) {
			tb_sw_info(sw,
				"changed while suspended (uid %#llx -> %#llx)\n",
				sw->uid, uid);
			return -ENODEV;
		}
	}

	/* upload configuration */
	err = tb_sw_write(sw, 1 + (u32 *) &sw->config, TB_CFG_SWITCH, 1, 3);
	if (err)
		return err;

	err = tb_plug_events_active(sw, true);
	if (err)
		return err;

	/* check for surviving downstream switches */
	for (i = 1; i <= sw->config.max_port_number; i++) {
		struct tb_port *port = &sw->ports[i];
		if (tb_is_upstream_port(port))
			continue;
		if (!port->remote)
			continue;
		if (tb_wait_for_port(port, true) <= 0
			|| tb_switch_resume(port->remote->sw)) {
			tb_port_warn(port,
				     "lost during suspend, disconnecting\n");
			tb_sw_set_unplugged(port->remote->sw);
		}
	}
	return 0;
}