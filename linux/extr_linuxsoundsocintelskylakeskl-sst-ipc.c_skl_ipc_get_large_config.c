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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sst_generic_ipc {int /*<<< orphan*/  dev; } ;
struct skl_ipc_large_config_msg {size_t param_data_size; int /*<<< orphan*/  large_param_id; int /*<<< orphan*/  module_id; int /*<<< orphan*/  instance_id; } ;
struct skl_ipc_header {int /*<<< orphan*/  extension; int /*<<< orphan*/  primary; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_DATA_OFFSET_SZ (size_t) ; 
 int /*<<< orphan*/  IPC_DATA_OFFSET_SZ_CLEAR ; 
 int /*<<< orphan*/  IPC_FINAL_BLOCK (int) ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_INITIAL_BLOCK (int) ; 
 int /*<<< orphan*/  IPC_INITIAL_BLOCK_CLEAR ; 
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
 int sst_ipc_tx_message_wait (struct sst_generic_ipc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 

int skl_ipc_get_large_config(struct sst_generic_ipc *ipc,
		struct skl_ipc_large_config_msg *msg, u32 *param)
{
	struct skl_ipc_header header = {0};
	u64 *ipc_header = (u64 *)(&header);
	int ret = 0;
	size_t sz_remaining, rx_size, data_offset;

	header.primary = IPC_MSG_TARGET(IPC_MOD_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_MOD_LARGE_CONFIG_GET);
	header.primary |= IPC_MOD_INSTANCE_ID(msg->instance_id);
	header.primary |= IPC_MOD_ID(msg->module_id);

	header.extension = IPC_DATA_OFFSET_SZ(msg->param_data_size);
	header.extension |= IPC_LARGE_PARAM_ID(msg->large_param_id);
	header.extension |= IPC_FINAL_BLOCK(1);
	header.extension |= IPC_INITIAL_BLOCK(1);

	sz_remaining = msg->param_data_size;
	data_offset = 0;

	while (sz_remaining != 0) {
		rx_size = sz_remaining > SKL_ADSP_W1_SZ
				? SKL_ADSP_W1_SZ : sz_remaining;
		if (rx_size == sz_remaining)
			header.extension |= IPC_FINAL_BLOCK(1);

		ret = sst_ipc_tx_message_wait(ipc, *ipc_header, NULL, 0,
					      ((char *)param) + data_offset,
					      msg->param_data_size);
		if (ret < 0) {
			dev_err(ipc->dev,
				"ipc: get large config fail, err: %d\n", ret);
			return ret;
		}
		sz_remaining -= rx_size;
		data_offset = msg->param_data_size - sz_remaining;

		/* clear the fields */
		header.extension &= IPC_INITIAL_BLOCK_CLEAR;
		header.extension &= IPC_DATA_OFFSET_SZ_CLEAR;
		/* fill the fields */
		header.extension |= IPC_INITIAL_BLOCK(1);
		header.extension |= IPC_DATA_OFFSET_SZ(data_offset);
	}

	return ret;
}