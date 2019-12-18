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
struct sst_ipc_message {int size; struct sst_hsw_ipc_fw_version* data; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct sst_hsw_ipc_fw_version {int dummy; } ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_GET_FW_VERSION ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,struct sst_ipc_message*) ; 

int sst_hsw_fw_get_version(struct sst_hsw *hsw,
	struct sst_hsw_ipc_fw_version *version)
{
	struct sst_ipc_message request = {0}, reply = {0};
	int ret;

	request.header = IPC_GLB_TYPE(IPC_GLB_GET_FW_VERSION);
	reply.data = version;
	reply.size = sizeof(*version);
	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, &reply);
	if (ret < 0)
		dev_err(hsw->dev, "error: get version failed\n");

	return ret;
}