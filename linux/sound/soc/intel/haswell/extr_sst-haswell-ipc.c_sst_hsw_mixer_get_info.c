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
struct sst_ipc_message {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct sst_hsw {int /*<<< orphan*/  mixer_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_GET_MIXER_STREAM_INFO ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,struct sst_ipc_message*) ; 
 int /*<<< orphan*/  trace_hsw_mixer_info_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int /*<<< orphan*/ ) ; 

int sst_hsw_mixer_get_info(struct sst_hsw *hsw)
{
	struct sst_ipc_message request = {0}, reply = {0};
	int ret;

	request.header = IPC_GLB_TYPE(IPC_GLB_GET_MIXER_STREAM_INFO);
	reply.data = &hsw->mixer_info;
	reply.size = sizeof(hsw->mixer_info);

	trace_ipc_request("get global mixer info", 0);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, &reply);
	if (ret < 0) {
		dev_err(hsw->dev, "error: get stream info failed\n");
		return ret;
	}

	trace_hsw_mixer_info_reply(&hsw->mixer_info);

	return 0;
}