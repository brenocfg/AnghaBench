#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tb_switch {int dummy; } ;
struct tb_port {int dummy; } ;
struct tb_pci_tunnel {int /*<<< orphan*/  list; } ;
struct tb_cm {int /*<<< orphan*/  tunnel_list; } ;
struct tb {TYPE_5__* root_switch; } ;
struct TYPE_6__ {int max_port_number; } ;
struct TYPE_10__ {TYPE_4__* ports; TYPE_1__ config; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_9__ {TYPE_3__* remote; TYPE_2__ config; } ;
struct TYPE_8__ {struct tb_switch* sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  TB_PORT_CAP_ADAP ; 
 scalar_t__ TB_TYPE_PORT ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tb_port* tb_find_pci_up_port (struct tb_switch*) ; 
 struct tb_port* tb_find_unused_down_port (TYPE_5__*) ; 
 scalar_t__ tb_is_upstream_port (TYPE_4__*) ; 
 scalar_t__ tb_pci_activate (struct tb_pci_tunnel*) ; 
 struct tb_pci_tunnel* tb_pci_alloc (struct tb*,struct tb_port*,struct tb_port*) ; 
 int /*<<< orphan*/  tb_pci_free (struct tb_pci_tunnel*) ; 
 int tb_port_find_cap (struct tb_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_port_info (struct tb_port*,char*) ; 
 scalar_t__ tb_port_read (struct tb_port*,int*,int /*<<< orphan*/ ,int,int) ; 
 struct tb_cm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  tb_sw_info (struct tb_switch*,char*) ; 

__attribute__((used)) static void tb_activate_pcie_devices(struct tb *tb)
{
	int i;
	int cap;
	u32 data;
	struct tb_switch *sw;
	struct tb_port *up_port;
	struct tb_port *down_port;
	struct tb_pci_tunnel *tunnel;
	struct tb_cm *tcm = tb_priv(tb);

	/* scan for pcie devices at depth 1*/
	for (i = 1; i <= tb->root_switch->config.max_port_number; i++) {
		if (tb_is_upstream_port(&tb->root_switch->ports[i]))
			continue;
		if (tb->root_switch->ports[i].config.type != TB_TYPE_PORT)
			continue;
		if (!tb->root_switch->ports[i].remote)
			continue;
		sw = tb->root_switch->ports[i].remote->sw;
		up_port = tb_find_pci_up_port(sw);
		if (!up_port) {
			tb_sw_info(sw, "no PCIe devices found, aborting\n");
			continue;
		}

		/* check whether port is already activated */
		cap = tb_port_find_cap(up_port, TB_PORT_CAP_ADAP);
		if (cap < 0)
			continue;
		if (tb_port_read(up_port, &data, TB_CFG_PORT, cap, 1))
			continue;
		if (data & 0x80000000) {
			tb_port_info(up_port,
				     "PCIe port already activated, aborting\n");
			continue;
		}

		down_port = tb_find_unused_down_port(tb->root_switch);
		if (!down_port) {
			tb_port_info(up_port,
				     "All PCIe down ports are occupied, aborting\n");
			continue;
		}
		tunnel = tb_pci_alloc(tb, up_port, down_port);
		if (!tunnel) {
			tb_port_info(up_port,
				     "PCIe tunnel allocation failed, aborting\n");
			continue;
		}

		if (tb_pci_activate(tunnel)) {
			tb_port_info(up_port,
				     "PCIe tunnel activation failed, aborting\n");
			tb_pci_free(tunnel);
			continue;
		}

		list_add(&tunnel->list, &tcm->tunnel_list);
	}
}