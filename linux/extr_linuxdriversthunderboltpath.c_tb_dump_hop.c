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
struct tb_regs_hop {char* unknown3; int /*<<< orphan*/  unknown2; int /*<<< orphan*/  unknown1; int /*<<< orphan*/  egress_shared_buffer; int /*<<< orphan*/  ingress_shared_buffer; int /*<<< orphan*/  egress_fc; int /*<<< orphan*/  ingress_fc; int /*<<< orphan*/  counter; int /*<<< orphan*/  counter_enable; int /*<<< orphan*/  drop_packages; int /*<<< orphan*/  initial_credits; int /*<<< orphan*/  priority; int /*<<< orphan*/  weight; scalar_t__ enable; int /*<<< orphan*/  next_hop; int /*<<< orphan*/  out_port; } ;
struct tb_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_port_info (struct tb_port*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void tb_dump_hop(struct tb_port *port, struct tb_regs_hop *hop)
{
	tb_port_info(port, " Hop through port %d to hop %d (%s)\n",
		     hop->out_port, hop->next_hop,
		     hop->enable ? "enabled" : "disabled");
	tb_port_info(port, "  Weight: %d Priority: %d Credits: %d Drop: %d\n",
		     hop->weight, hop->priority,
		     hop->initial_credits, hop->drop_packages);
	tb_port_info(port, "   Counter enabled: %d Counter index: %d\n",
		     hop->counter_enable, hop->counter);
	tb_port_info(port, "  Flow Control (In/Eg): %d/%d Shared Buffer (In/Eg): %d/%d\n",
		     hop->ingress_fc, hop->egress_fc,
		     hop->ingress_shared_buffer, hop->egress_shared_buffer);
	tb_port_info(port, "  Unknown1: %#x Unknown2: %#x Unknown3: %#x\n",
		     hop->unknown1, hop->unknown2, hop->unknown3);
}