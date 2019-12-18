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
struct TYPE_2__ {int /*<<< orphan*/  stream_hw_id; } ;
struct sst_hsw_stream {TYPE_1__ reply; } ;
struct sst_hsw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_STR_PAUSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int sst_hsw_stream_operations (struct sst_hsw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int /*<<< orphan*/ ) ; 

int sst_hsw_stream_pause(struct sst_hsw *hsw, struct sst_hsw_stream *stream,
	int wait)
{
	int ret;

	if (!stream) {
		dev_warn(hsw->dev, "warning: stream is NULL, no stream to pause, ignore it.\n");
		return 0;
	}

	trace_ipc_request("stream pause", stream->reply.stream_hw_id);

	ret = sst_hsw_stream_operations(hsw, IPC_STR_PAUSE,
		stream->reply.stream_hw_id, wait);
	if (ret < 0)
		dev_err(hsw->dev, "error: failed to pause stream %d\n",
			stream->reply.stream_hw_id);

	return ret;
}