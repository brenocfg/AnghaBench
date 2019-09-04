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
typedef  int /*<<< orphan*/  u64 ;
struct sst_generic_ipc {int /*<<< orphan*/  dev; } ;
struct skl_ipc_header {int /*<<< orphan*/  primary; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_FW_GEN_MSG ; 
 int /*<<< orphan*/  IPC_GLB_LOAD_LIBRARY ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MOD_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MOD_INSTANCE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MSG_DIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MSG_REQUEST ; 
 int /*<<< orphan*/  IPC_MSG_TARGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_nowait (struct sst_generic_ipc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (struct sst_generic_ipc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int skl_sst_ipc_load_library(struct sst_generic_ipc *ipc,
				u8 dma_id, u8 table_id, bool wait)
{
	struct skl_ipc_header header = {0};
	u64 *ipc_header = (u64 *)(&header);
	int ret = 0;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_LOAD_LIBRARY);
	header.primary |= IPC_MOD_INSTANCE_ID(table_id);
	header.primary |= IPC_MOD_ID(dma_id);

	if (wait)
		ret = sst_ipc_tx_message_wait(ipc, *ipc_header,
					NULL, 0, NULL, 0);
	else
		ret = sst_ipc_tx_message_nowait(ipc, *ipc_header, NULL, 0);

	if (ret < 0)
		dev_err(ipc->dev, "ipc: load lib failed\n");

	return ret;
}