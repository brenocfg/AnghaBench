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
struct TYPE_4__ {int max_port_number; } ;
struct tb_switch {TYPE_3__* ports; TYPE_1__ config; } ;
struct TYPE_6__ {TYPE_2__* remote; } ;
struct TYPE_5__ {struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_is_upstream_port (TYPE_3__*) ; 
 int tb_plug_events_active (struct tb_switch*,int) ; 

void tb_switch_suspend(struct tb_switch *sw)
{
	int i, err;
	err = tb_plug_events_active(sw, false);
	if (err)
		return;

	for (i = 1; i <= sw->config.max_port_number; i++) {
		if (!tb_is_upstream_port(&sw->ports[i]) && sw->ports[i].remote)
			tb_switch_suspend(sw->ports[i].remote->sw);
	}
	/*
	 * TODO: invoke tb_cfg_prepare_to_sleep here? does not seem to have any
	 * effect?
	 */
}