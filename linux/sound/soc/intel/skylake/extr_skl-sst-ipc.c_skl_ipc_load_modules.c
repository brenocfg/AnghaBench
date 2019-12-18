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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct sst_ipc_message {int size; void* data; int /*<<< orphan*/  header; } ;
struct sst_generic_ipc {int /*<<< orphan*/  dev; } ;
struct skl_ipc_header {int /*<<< orphan*/  primary; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_FW_GEN_MSG ; 
 int /*<<< orphan*/  IPC_GLB_LOAD_MULTIPLE_MODS ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_LOAD_MODULE_CNT (int) ; 
 int /*<<< orphan*/  IPC_MSG_DIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_MSG_REQUEST ; 
 int /*<<< orphan*/  IPC_MSG_TARGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sst_ipc_tx_message_nowait (struct sst_generic_ipc*,struct sst_ipc_message) ; 

int skl_ipc_load_modules(struct sst_generic_ipc *ipc,
				u8 module_cnt, void *data)
{
	struct skl_ipc_header header = {0};
	struct sst_ipc_message request;
	int ret;

	header.primary = IPC_MSG_TARGET(IPC_FW_GEN_MSG);
	header.primary |= IPC_MSG_DIR(IPC_MSG_REQUEST);
	header.primary |= IPC_GLB_TYPE(IPC_GLB_LOAD_MULTIPLE_MODS);
	header.primary |= IPC_LOAD_MODULE_CNT(module_cnt);

	request.header = *(u64 *)(&header);
	request.data = data;
	request.size = sizeof(u16) * module_cnt;

	ret = sst_ipc_tx_message_nowait(ipc, request);
	if (ret < 0)
		dev_err(ipc->dev, "ipc: load modules failed :%d\n", ret);

	return ret;
}