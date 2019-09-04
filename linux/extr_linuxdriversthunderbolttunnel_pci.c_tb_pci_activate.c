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
struct tb_pci_tunnel {TYPE_2__* path_to_down; TYPE_1__* path_to_up; } ;
struct TYPE_4__ {scalar_t__ activated; } ;
struct TYPE_3__ {scalar_t__ activated; } ;

/* Variables and functions */
 int EINVAL ; 
 int tb_pci_restart (struct tb_pci_tunnel*) ; 
 int /*<<< orphan*/  tb_tunnel_WARN (struct tb_pci_tunnel*,char*) ; 

int tb_pci_activate(struct tb_pci_tunnel *tunnel)
{
	if (tunnel->path_to_up->activated || tunnel->path_to_down->activated) {
		tb_tunnel_WARN(tunnel,
			       "trying to activate an already activated tunnel\n");
		return -EINVAL;
	}

	return tb_pci_restart(tunnel);
}