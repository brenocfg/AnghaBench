#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sst_ipc_message {int header; int size; struct sst_hsw_ipc_volume_req* data; } ;
struct sst_hsw_ipc_volume_req {int target_volume; int channel; } ;
struct TYPE_2__ {int stream_hw_id; } ;
struct sst_hsw_stream {struct sst_hsw_ipc_volume_req vol_req; TYPE_1__ reply; } ;
struct sst_hsw {int* mute_volume; int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; scalar_t__* mute; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPC_GLB_STREAM_MESSAGE ; 
 int IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int IPC_STG_ID_SHIFT ; 
 int IPC_STG_SET_VOLUME ; 
 int IPC_STG_TYPE_SHIFT ; 
 int IPC_STR_ID_SHIFT ; 
 int /*<<< orphan*/  IPC_STR_STAGE_MESSAGE ; 
 int IPC_STR_TYPE (int /*<<< orphan*/ ) ; 
 int SST_HSW_CHANNELS_ALL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int) ; 

int sst_hsw_stream_set_volume(struct sst_hsw *hsw,
	struct sst_hsw_stream *stream, u32 stage_id, u32 channel, u32 volume)
{
	struct sst_hsw_ipc_volume_req *req;
	struct sst_ipc_message request;
	int ret;

	trace_ipc_request("set stream volume", stream->reply.stream_hw_id);

	if (channel >= 2 && channel != SST_HSW_CHANNELS_ALL)
		return -EINVAL;

	request.header = IPC_GLB_TYPE(IPC_GLB_STREAM_MESSAGE) |
		IPC_STR_TYPE(IPC_STR_STAGE_MESSAGE);
	request.header |= (stream->reply.stream_hw_id << IPC_STR_ID_SHIFT);
	request.header |= (IPC_STG_SET_VOLUME << IPC_STG_TYPE_SHIFT);
	request.header |= (stage_id << IPC_STG_ID_SHIFT);

	req = &stream->vol_req;
	req->target_volume = volume;

	/* set both at same time ? */
	if (channel == SST_HSW_CHANNELS_ALL) {
		if (hsw->mute[0] && hsw->mute[1]) {
			hsw->mute_volume[0] = hsw->mute_volume[1] = volume;
			return 0;
		} else if (hsw->mute[0])
			req->channel = 1;
		else if (hsw->mute[1])
			req->channel = 0;
		else
			req->channel = SST_HSW_CHANNELS_ALL;
	} else {
		/* set only 1 channel */
		if (hsw->mute[channel]) {
			hsw->mute_volume[channel] = volume;
			return 0;
		}
		req->channel = channel;
	}

	request.data = req;
	request.size = sizeof(*req);
	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, NULL);
	if (ret < 0) {
		dev_err(hsw->dev, "error: set stream volume failed\n");
		return ret;
	}

	return 0;
}