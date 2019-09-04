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
struct tb_pci_tunnel {int /*<<< orphan*/  up_port; int /*<<< orphan*/  down_port; TYPE_1__* path_to_down; TYPE_1__* path_to_up; } ;
struct TYPE_2__ {int activated; } ;

/* Variables and functions */
 int tb_path_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_pci_deactivate (struct tb_pci_tunnel*) ; 
 int tb_pci_port_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_tunnel_info (struct tb_pci_tunnel*,char*) ; 
 int /*<<< orphan*/  tb_tunnel_warn (struct tb_pci_tunnel*,char*) ; 

int tb_pci_restart(struct tb_pci_tunnel *tunnel)
{
	int res;
	tunnel->path_to_up->activated = false;
	tunnel->path_to_down->activated = false;

	tb_tunnel_info(tunnel, "activating\n");

	res = tb_path_activate(tunnel->path_to_up);
	if (res)
		goto err;
	res = tb_path_activate(tunnel->path_to_down);
	if (res)
		goto err;

	res = tb_pci_port_active(tunnel->down_port, true);
	if (res)
		goto err;

	res = tb_pci_port_active(tunnel->up_port, true);
	if (res)
		goto err;
	return 0;
err:
	tb_tunnel_warn(tunnel, "activation failed\n");
	tb_pci_deactivate(tunnel);
	return res;
}