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
typedef  int u64 ;
typedef  unsigned int u32 ;
struct sst_ipc_message {unsigned int* data; int header; size_t size; int /*<<< orphan*/  member_0; } ;
struct sst_generic_ipc {int /*<<< orphan*/  dev; } ;
struct skl_ipc_large_config_msg {int /*<<< orphan*/  large_param_id; int /*<<< orphan*/  param_data_size; int /*<<< orphan*/  module_id; int /*<<< orphan*/  instance_id; } ;
struct skl_ipc_header {int /*<<< orphan*/  extension; int /*<<< orphan*/  primary; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPC_DATA_OFFSET_SZ (int /*<<< orphan*/ ) ; 
 int IPC_DATA_OFFSET_SZ_MASK ; 
 int /*<<< orphan*/  IPC_FINAL_BLOCK (int) ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_INITIAL_BLOCK (int) ; 
 int /*<<< orphan*/  IPC_LARGE_PARAM_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MOD_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MOD_INSTANCE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MOD_LARGE_CONFIG_GET ; 
 int /*<<< orphan*/  IPC_MOD_MSG ; 
 int /*<<< orphan*/  IPC_MSG_DIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MSG_REQUEST ; 
 int /*<<< orphan*/  IPC_MSG_TARGET (int /*<<< orphan*/ ) ; 
 size_t SKL_ADSP_W1_SZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int* krealloc (unsigned int*,int,int /*<<< orphan*/ ) ; 
 unsigned int* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (struct sst_generic_ipc*,struct sst_ipc_message,struct sst_ipc_message*) ; 

int skl_ipc_get_large_config(struct sst_generic_ipc *ipc,
		struct skl_ipc_large_config_msg *msg,
		u32 **payload, size_t *bytes)
{
	struct skl_ipc_header header = {0};
	struct sst_ipc_message request, reply = {0};
	unsigned int *buf;
	int ret;

	reply.data = kzalloc(SKL_ADSP_W1_SZ, GFP_KERNEL);
	if (!reply.data)
		return -ENOMEM;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_LARGE_CONFIG_GET);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_DATA_OFFSET_SZ(msg->param_data_size);
	header.extension |= IPC_LARGE_PARAM_ID(msg->large_param_id);
	header.extension |= IPC_FINAL_BLOCK(1);
	header.extension |= IPC_INITIAL_BLOCK(1);

	request.header = *(u64 *)&header;
	request.data = *payload;
	request.size = *bytes;
	reply.size = SKL_ADSP_W1_SZ;

	ret = sst_ipc_tx_message_wait(ipc, request, &reply);
	if (ret < 0)
		dev_err(ipc->dev, "ipc: get large config fail, err: %d\n", ret);

	reply.size = (reply.header >> 32) & IPC_DATA_OFFSET_SZ_MASK;
	buf = krealloc(reply.data, reply.size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	*payload = buf;
	*bytes = reply.size;

	return ret;
}