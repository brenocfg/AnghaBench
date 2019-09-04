#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int max_port_number; } ;
struct tb_switch {int is_unplugged; TYPE_4__* ports; TYPE_1__ config; TYPE_3__* tb; } ;
struct TYPE_8__ {TYPE_2__* remote; } ;
struct TYPE_7__ {struct tb_switch* root_switch; } ;
struct TYPE_6__ {struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_is_upstream_port (TYPE_4__*) ; 
 int /*<<< orphan*/  tb_sw_WARN (struct tb_switch*,char*) ; 

void tb_sw_set_unplugged(struct tb_switch *sw)
{
	int i;
	if (sw == sw->tb->root_switch) {
		tb_sw_WARN(sw, "cannot unplug root switch\n");
		return;
	}
	if (sw->is_unplugged) {
		tb_sw_WARN(sw, "is_unplugged already set\n");
		return;
	}
	sw->is_unplugged = true;
	for (i = 0; i <= sw->config.max_port_number; i++) {
		if (!tb_is_upstream_port(&sw->ports[i]) && sw->ports[i].remote)
			tb_sw_set_unplugged(sw->ports[i].remote->sw);
	}
}