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
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipipe_get_lutdpc_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_lutdpc *lut_param = param;
	struct vpfe_ipipe_lutdpc *lutdpc = &ipipe->config.lutdpc;

	lut_param->en = lutdpc->en;
	lut_param->repl_white = lutdpc->repl_white;
	lut_param->dpc_size = lutdpc->dpc_size;
	memcpy(&lut_param->table, &lutdpc->table,
	   (lutdpc->dpc_size * sizeof(struct vpfe_ipipe_lutdpc_entry)));

	return 0;
}