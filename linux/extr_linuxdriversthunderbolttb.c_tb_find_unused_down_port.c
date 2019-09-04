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
struct TYPE_3__ {int max_port_number; } ;
struct tb_switch {struct tb_port* ports; TYPE_1__ config; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct tb_port {TYPE_2__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  TB_PORT_CAP_ADAP ; 
 scalar_t__ TB_TYPE_PCIE_DOWN ; 
 scalar_t__ tb_is_upstream_port (struct tb_port*) ; 
 int tb_port_find_cap (struct tb_port*,int /*<<< orphan*/ ) ; 
 int tb_port_read (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct tb_port *tb_find_unused_down_port(struct tb_switch *sw)
{
	int i;
	int cap;
	int res;
	int data;
	for (i = 1; i <= sw->config.max_port_number; i++) {
		if (tb_is_upstream_port(&sw->ports[i]))
			continue;
		if (sw->ports[i].config.type != TB_TYPE_PCIE_DOWN)
			continue;
		cap = tb_port_find_cap(&sw->ports[i], TB_PORT_CAP_ADAP);
		if (cap < 0)
			continue;
		res = tb_port_read(&sw->ports[i], &data, TB_CFG_PORT, cap, 1);
		if (res < 0)
			continue;
		if (data & 0x80000000)
			continue;
		return &sw->ports[i];
	}
	return NULL;
}