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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct pnp_bios_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_DS ; 
 int PNP_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_SET_SYS_DEV_NODE ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pnp_bios_node*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 
 scalar_t__ pnpbios_dont_use_current_config ; 

__attribute__((used)) static int __pnp_bios_set_dev_node(u8 nodenum, char boot,
				   struct pnp_bios_node *data)
{
	u16 status;

	if (!pnp_bios_present())
		return PNP_FUNCTION_NOT_SUPPORTED;
	if (!boot && pnpbios_dont_use_current_config)
		return PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_SET_SYS_DEV_NODE, nodenum, 0, PNP_TS1,
			       boot ? 2 : 1, PNP_DS, 0, 0, data, 65536, NULL,
			       0);
	return status;
}