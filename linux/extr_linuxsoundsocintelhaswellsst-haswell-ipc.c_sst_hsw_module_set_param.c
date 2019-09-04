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
struct sst_hsw_transfer_parameter {int parameter_id; int data_size; int /*<<< orphan*/  data; } ;
struct sst_hsw_transfer_list {int dummy; } ;
struct sst_hsw {int /*<<< orphan*/  ipc; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPC_GLB_MODULE_OPERATION ; 
 int IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int IPC_MODULE_ID (int) ; 
 int IPC_MODULE_OPERATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MODULE_SET_PARAMETER ; 
 int SST_HSW_IPC_MAX_SHORT_PARAMETER_SIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct sst_hsw_transfer_parameter*) ; 
 struct sst_hsw_transfer_parameter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int,struct sst_hsw_transfer_parameter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sst_hsw_module_set_param(struct sst_hsw *hsw,
	u32 module_id, u32 instance_id, u32 parameter_id,
	u32 param_size, char *param)
{
	int ret;
	u32 header = 0;
	u32 payload_size = 0, transfer_parameter_size = 0;
	struct sst_hsw_transfer_parameter *parameter;
	struct device *dev = hsw->dev;

	header = IPC_GLB_TYPE(IPC_GLB_MODULE_OPERATION) |
			IPC_MODULE_OPERATION(IPC_MODULE_SET_PARAMETER) |
			IPC_MODULE_ID(module_id);
	dev_dbg(dev, "sst_hsw_module_set_param header=%x\n", header);

	payload_size = param_size +
		sizeof(struct sst_hsw_transfer_parameter) -
		sizeof(struct sst_hsw_transfer_list);
	dev_dbg(dev, "parameter size : %d\n", param_size);
	dev_dbg(dev, "payload size   : %d\n", payload_size);

	if (payload_size <= SST_HSW_IPC_MAX_SHORT_PARAMETER_SIZE) {
		/* short parameter, mailbox can contain data */
		dev_dbg(dev, "transfer parameter size : %d\n",
			transfer_parameter_size);

		transfer_parameter_size = ALIGN(payload_size, 4);
		dev_dbg(dev, "transfer parameter aligned size : %d\n",
			transfer_parameter_size);

		parameter = kzalloc(transfer_parameter_size, GFP_KERNEL);
		if (parameter == NULL)
			return -ENOMEM;

		memcpy(parameter->data, param, param_size);
	} else {
		dev_warn(dev, "transfer parameter size too large!");
		return 0;
	}

	parameter->parameter_id = parameter_id;
	parameter->data_size = param_size;

	ret = sst_ipc_tx_message_wait(&hsw->ipc, header,
		parameter, transfer_parameter_size , NULL, 0);
	if (ret < 0)
		dev_err(dev, "ipc: module set parameter failed - %d\n", ret);

	kfree(parameter);

	return ret;
}