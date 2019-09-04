#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tb_regs_hop {int initial_credits; int enable; int counter; int counter_enable; int ingress_fc; int egress_fc; int ingress_shared_buffer; int egress_shared_buffer; scalar_t__ unknown3; int /*<<< orphan*/  drop_packages; int /*<<< orphan*/  priority; scalar_t__ unknown2; int /*<<< orphan*/  weight; scalar_t__ unknown1; int /*<<< orphan*/  out_port; int /*<<< orphan*/  next_hop; int /*<<< orphan*/  member_0; } ;
struct tb_path {int activated; int path_length; int ingress_fc_enable; int egress_fc_enable; int ingress_shared_buffer; int egress_shared_buffer; int /*<<< orphan*/  tb; TYPE_2__* hops; int /*<<< orphan*/  drop_packages; int /*<<< orphan*/  priority; int /*<<< orphan*/  weight; int /*<<< orphan*/  nfc_credits; } ;
typedef  enum tb_path_port { ____Placeholder_tb_path_port } tb_path_port ;
struct TYPE_10__ {int /*<<< orphan*/  port; int /*<<< orphan*/  sw; } ;
struct TYPE_9__ {int in_counter_index; int in_hop_index; TYPE_3__* in_port; TYPE_1__* out_port; int /*<<< orphan*/  next_hop_index; } ;
struct TYPE_8__ {int /*<<< orphan*/  port; int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TB_CFG_HOPS ; 
 int TB_PATH_DESTINATION ; 
 int TB_PATH_INTERNAL ; 
 int TB_PATH_SOURCE ; 
 int /*<<< orphan*/  __tb_path_deactivate_hops (struct tb_path*,int) ; 
 int /*<<< orphan*/  __tb_path_deallocate_nfc (struct tb_path*,int) ; 
 int /*<<< orphan*/  tb_WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tb_dump_hop (TYPE_3__*,struct tb_regs_hop*) ; 
 int /*<<< orphan*/  tb_info (int /*<<< orphan*/ ,char*,...) ; 
 int tb_port_add_nfc_credits (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int tb_port_clear_counter (TYPE_3__*,int) ; 
 int /*<<< orphan*/  tb_port_info (TYPE_3__*,char*,int,int) ; 
 int tb_port_write (TYPE_3__*,struct tb_regs_hop*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tb_route (int /*<<< orphan*/ ) ; 

int tb_path_activate(struct tb_path *path)
{
	int i, res;
	enum tb_path_port out_mask, in_mask;
	if (path->activated) {
		tb_WARN(path->tb, "trying to activate already activated path\n");
		return -EINVAL;
	}

	tb_info(path->tb,
		"activating path from %llx:%x to %llx:%x\n",
		tb_route(path->hops[0].in_port->sw),
		path->hops[0].in_port->port,
		tb_route(path->hops[path->path_length - 1].out_port->sw),
		path->hops[path->path_length - 1].out_port->port);

	/* Clear counters. */
	for (i = path->path_length - 1; i >= 0; i--) {
		if (path->hops[i].in_counter_index == -1)
			continue;
		res = tb_port_clear_counter(path->hops[i].in_port,
					    path->hops[i].in_counter_index);
		if (res)
			goto err;
	}

	/* Add non flow controlled credits. */
	for (i = path->path_length - 1; i >= 0; i--) {
		res = tb_port_add_nfc_credits(path->hops[i].in_port,
					      path->nfc_credits);
		if (res) {
			__tb_path_deallocate_nfc(path, i);
			goto err;
		}
	}

	/* Activate hops. */
	for (i = path->path_length - 1; i >= 0; i--) {
		struct tb_regs_hop hop = { 0 };

		/*
		 * We do (currently) not tear down paths setup by the firmeware.
		 * If a firmware device is unplugged and plugged in again then
		 * it can happen that we reuse some of the hops from the (now
		 * defunct) firmeware path. This causes the hotplug operation to
		 * fail (the pci device does not show up). Clearing the hop
		 * before overwriting it fixes the problem.
		 *
		 * Should be removed once we discover and tear down firmeware
		 * paths.
		 */
		res = tb_port_write(path->hops[i].in_port, &hop, TB_CFG_HOPS,
				    2 * path->hops[i].in_hop_index, 2);
		if (res) {
			__tb_path_deactivate_hops(path, i);
			__tb_path_deallocate_nfc(path, 0);
			goto err;
		}

		/* dword 0 */
		hop.next_hop = path->hops[i].next_hop_index;
		hop.out_port = path->hops[i].out_port->port;
		/* TODO: figure out why these are good values */
		hop.initial_credits = (i == path->path_length - 1) ? 16 : 7;
		hop.unknown1 = 0;
		hop.enable = 1;

		/* dword 1 */
		out_mask = (i == path->path_length - 1) ?
				TB_PATH_DESTINATION : TB_PATH_INTERNAL;
		in_mask = (i == 0) ? TB_PATH_SOURCE : TB_PATH_INTERNAL;
		hop.weight = path->weight;
		hop.unknown2 = 0;
		hop.priority = path->priority;
		hop.drop_packages = path->drop_packages;
		hop.counter = path->hops[i].in_counter_index;
		hop.counter_enable = path->hops[i].in_counter_index != -1;
		hop.ingress_fc = path->ingress_fc_enable & in_mask;
		hop.egress_fc = path->egress_fc_enable & out_mask;
		hop.ingress_shared_buffer = path->ingress_shared_buffer
					    & in_mask;
		hop.egress_shared_buffer = path->egress_shared_buffer
					    & out_mask;
		hop.unknown3 = 0;

		tb_port_info(path->hops[i].in_port, "Writing hop %d, index %d",
			     i, path->hops[i].in_hop_index);
		tb_dump_hop(path->hops[i].in_port, &hop);
		res = tb_port_write(path->hops[i].in_port, &hop, TB_CFG_HOPS,
				    2 * path->hops[i].in_hop_index, 2);
		if (res) {
			__tb_path_deactivate_hops(path, i);
			__tb_path_deallocate_nfc(path, 0);
			goto err;
		}
	}
	path->activated = true;
	tb_info(path->tb, "path activation complete\n");
	return 0;
err:
	tb_WARN(path->tb, "path activation failed\n");
	return res;
}