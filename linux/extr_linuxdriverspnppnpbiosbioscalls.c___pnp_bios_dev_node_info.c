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
typedef  int u16 ;
struct pnp_dev_node_info {int no_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNP_DS ; 
 int PNP_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PNP_GET_NUM_SYS_DEV_NODES ; 
 int /*<<< orphan*/  PNP_TS1 ; 
 int call_pnp_bios (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pnp_dev_node_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_bios_present () ; 

__attribute__((used)) static int __pnp_bios_dev_node_info(struct pnp_dev_node_info *data)
{
	u16 status;

	if (!pnp_bios_present())
		return PNP_FUNCTION_NOT_SUPPORTED;
	status = call_pnp_bios(PNP_GET_NUM_SYS_DEV_NODES, 0, PNP_TS1, 2,
			       PNP_TS1, PNP_DS, 0, 0, data,
			       sizeof(struct pnp_dev_node_info), NULL, 0);
	data->no_nodes &= 0xff;
	return status;
}