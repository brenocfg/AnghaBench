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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pvt_id; int /*<<< orphan*/  module_id; } ;
struct skl_module_cfg {TYPE_1__ id; } ;
struct skl_ipc_large_config_msg {int param_data_size; int /*<<< orphan*/  large_param_id; int /*<<< orphan*/  instance_id; int /*<<< orphan*/  module_id; } ;
struct skl_dev {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int skl_ipc_set_large_config (int /*<<< orphan*/ *,struct skl_ipc_large_config_msg*,int /*<<< orphan*/ *) ; 

int skl_set_module_params(struct skl_dev *skl, u32 *params, int size,
				u32 param_id, struct skl_module_cfg *mcfg)
{
	struct skl_ipc_large_config_msg msg;

	msg.module_id = mcfg->id.module_id;
	msg.instance_id = mcfg->id.pvt_id;
	msg.param_data_size = size;
	msg.large_param_id = param_id;

	return skl_ipc_set_large_config(&skl->ipc, &msg, params);
}