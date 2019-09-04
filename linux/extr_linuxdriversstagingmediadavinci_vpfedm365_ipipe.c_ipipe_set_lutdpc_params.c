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
struct vpfe_ipipe_lutdpc_entry {int dummy; } ;
struct vpfe_ipipe_lutdpc {int dpc_size; int /*<<< orphan*/  table; int /*<<< orphan*/  repl_white; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {struct vpfe_ipipe_lutdpc lutdpc; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  isp5_base_addr; int /*<<< orphan*/  base_addr; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ipipe_set_lutdpc_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vpfe_ipipe_lutdpc*) ; 
 scalar_t__ ipipe_validate_lutdpc_params (struct vpfe_ipipe_lutdpc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_lutdpc_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_lutdpc *lutdpc = &ipipe->config.lutdpc;
	struct vpfe_ipipe_lutdpc *dpc_param;

	if (!param) {
		memset((void *)lutdpc, 0, sizeof(struct vpfe_ipipe_lutdpc));
		goto success;
	}

	dpc_param = param;
	lutdpc->en = dpc_param->en;
	lutdpc->repl_white = dpc_param->repl_white;
	lutdpc->dpc_size = dpc_param->dpc_size;
	memcpy(&lutdpc->table, &dpc_param->table,
	       (dpc_param->dpc_size * sizeof(struct vpfe_ipipe_lutdpc_entry)));
	if (ipipe_validate_lutdpc_params(lutdpc) < 0)
		return -EINVAL;

success:
	ipipe_set_lutdpc_regs(ipipe->base_addr, ipipe->isp5_base_addr, lutdpc);

	return 0;
}