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
struct pnp_isa_config_struc {int dummy; } ;

/* Variables and functions */
 int __pnp_bios_isapnp_config (struct pnp_isa_config_struc*) ; 
 int /*<<< orphan*/  pnpbios_print_status (char*,int) ; 

int pnp_bios_isapnp_config(struct pnp_isa_config_struc *data)
{
	int status;

	status = __pnp_bios_isapnp_config(data);
	if (status)
		pnpbios_print_status("isapnp_config", status);
	return status;
}