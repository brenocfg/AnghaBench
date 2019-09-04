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
typedef  int /*<<< orphan*/  u32 ;
struct sst_hsw_ipc_stream_info_reply {int dummy; } ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; struct sst_hsw_ipc_stream_info_reply mixer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_GET_MIXER_STREAM_INFO ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sst_hsw_ipc_stream_info_reply*,int) ; 
 int /*<<< orphan*/  trace_hsw_mixer_info_reply (struct sst_hsw_ipc_stream_info_reply*) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int /*<<< orphan*/ ) ; 

int sst_hsw_mixer_get_info(struct sst_hsw *hsw)
{
	struct sst_hsw_ipc_stream_info_reply *reply;
	u32 header;
	int ret;

	reply = &hsw->mixer_info;
	header = IPC_GLB_TYPE(IPC_GLB_GET_MIXER_STREAM_INFO);

	trace_ipc_request("get global mixer info", 0);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, header, NULL, 0,
		reply, sizeof(*reply));
	if (ret < 0) {
		dev_err(hsw->dev, "error: get stream info failed\n");
		return ret;
	}

	trace_hsw_mixer_info_reply(reply);

	return 0;
}