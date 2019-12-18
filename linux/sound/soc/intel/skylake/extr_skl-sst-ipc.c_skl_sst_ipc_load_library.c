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
struct sst_ipc_message {int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
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
 int sst_ipc_tx_message_nowait (struct sst_generic_ipc*,struct sst_ipc_message) ; 
 int sst_ipc_tx_message_wait (struct sst_generic_ipc*,struct sst_ipc_message,int /*<<< orphan*/ *) ; 

int skl_sst_ipc_load_library(struct sst_generic_ipc *ipc,
				u8 dma_id, u8 table_id, bool wait)
{
	struct skl_ipc_header header = {0};
	struct sst_ipc_message request = {0};
	int ret = 0;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_LOAD_LIBRARY);
	header.primary |= IPC_MOD_INSTANCE_ID(table_id);
	header.primary |= IPC_MOD_ID(dma_id);
	request.header = *(u64 *)(&header);

	if (wait)
		ret = sst_ipc_tx_message_wait(ipc, request, NULL);
	else
		ret = sst_ipc_tx_message_nowait(ipc, request);

	if (ret < 0)
		dev_err(ipc->dev, "ipc: load lib failed\n");

	return ret;
}