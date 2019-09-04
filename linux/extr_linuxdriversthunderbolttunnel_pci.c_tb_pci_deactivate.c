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
struct tb_pci_tunnel {TYPE_1__* path_to_up; TYPE_1__* path_to_down; int /*<<< orphan*/  down_port; int /*<<< orphan*/  up_port; } ;
struct TYPE_2__ {scalar_t__ activated; } ;

/* Variables and functions */
 int /*<<< orphan*/  tb_path_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_pci_port_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_tunnel_info (struct tb_pci_tunnel*,char*) ; 

void tb_pci_deactivate(struct tb_pci_tunnel *tunnel)
{
	tb_tunnel_info(tunnel, "deactivating\n");
	/*
	 * TODO: enable reset by writing 0x04000000 to TB_CAP_PCIE + 1 on up
	 * port. Seems to have no effect?
	 */
	tb_pci_port_active(tunnel->up_port, false);
	tb_pci_port_active(tunnel->down_port, false);
	if (tunnel->path_to_down->activated)
		tb_path_deactivate(tunnel->path_to_down);
	if (tunnel->path_to_up->activated)
		tb_path_deactivate(tunnel->path_to_up);
}