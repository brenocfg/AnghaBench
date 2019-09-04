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
struct pnp_bios_node {int handle; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  pnpbios_dont_use_current_config ; 
 int /*<<< orphan*/  pnpbios_proc_fops ; 
 scalar_t__ proc_create_data (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  proc_pnp ; 
 int /*<<< orphan*/  proc_pnp_boot ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int pnpbios_interface_attach_device(struct pnp_bios_node *node)
{
	char name[3];

	sprintf(name, "%02x", node->handle);

	if (!proc_pnp)
		return -EIO;
	if (!pnpbios_dont_use_current_config) {
		proc_create_data(name, 0644, proc_pnp, &pnpbios_proc_fops,
				 (void *)(long)(node->handle));
	}

	if (!proc_pnp_boot)
		return -EIO;
	if (proc_create_data(name, 0644, proc_pnp_boot, &pnpbios_proc_fops,
			     (void *)(long)(node->handle + 0x100)))
		return 0;
	return -EIO;
}