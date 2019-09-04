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
struct tb_pci_tunnel {TYPE_1__* path_to_down; TYPE_1__* path_to_up; } ;
struct TYPE_2__ {scalar_t__ activated; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tb_pci_tunnel*) ; 
 int /*<<< orphan*/  tb_path_free (TYPE_1__*) ; 
 int /*<<< orphan*/  tb_tunnel_WARN (struct tb_pci_tunnel*,char*) ; 

void tb_pci_free(struct tb_pci_tunnel *tunnel)
{
	if (tunnel->path_to_up->activated || tunnel->path_to_down->activated) {
		tb_tunnel_WARN(tunnel, "trying to free an activated tunnel\n");
		return;
	}
	tb_path_free(tunnel->path_to_up);
	tb_path_free(tunnel->path_to_down);
	kfree(tunnel);
}