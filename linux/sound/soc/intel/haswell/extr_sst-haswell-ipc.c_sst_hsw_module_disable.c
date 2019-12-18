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
typedef  int u32 ;
struct sst_module {int /*<<< orphan*/  state; } ;
struct sst_ipc_message {int header; int /*<<< orphan*/  member_0; } ;
struct sst_hsw {int /*<<< orphan*/  ipc; struct sst_dsp* dsp; struct device* dev; } ;
struct sst_dsp {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IPC_GLB_MODULE_OPERATION ; 
 int IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MODULE_DISABLE ; 
 int IPC_MODULE_ID (int) ; 
 int IPC_MODULE_OPERATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SST_MODULE_STATE_INITIALIZED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  sst_hsw_is_module_active (struct sst_hsw*,int) ; 
 int /*<<< orphan*/  sst_hsw_is_module_loaded (struct sst_hsw*,int) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 
 struct sst_module* sst_module_get_from_id (struct sst_dsp*,int) ; 

int sst_hsw_module_disable(struct sst_hsw *hsw,
	u32 module_id, u32 instance_id)
{
	int ret;
	struct sst_ipc_message request = {0};
	struct sst_module *module;
	struct device *dev = hsw->dev;
	struct sst_dsp *dsp = hsw->dsp;

	if (!sst_hsw_is_module_loaded(hsw, module_id)) {
		dev_dbg(dev, "module %d not loaded\n", module_id);
		return 0;
	}

	if (!sst_hsw_is_module_active(hsw, module_id)) {
		dev_info(dev, "module %d already disabled\n", module_id);
		return 0;
	}

	module = sst_module_get_from_id(dsp, module_id);
	if (module == NULL) {
		dev_err(dev, "module %d not valid\n", module_id);
		return -ENXIO;
	}

	request.header = IPC_GLB_TYPE(IPC_GLB_MODULE_OPERATION) |
			IPC_MODULE_OPERATION(IPC_MODULE_DISABLE) |
			IPC_MODULE_ID(module_id);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, NULL);
	if (ret < 0)
		dev_err(dev, "module disable failed - %d\n", ret);
	else
		module->state = SST_MODULE_STATE_INITIALIZED;

	return ret;
}