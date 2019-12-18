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
struct sst_hsw_stream {int commited; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/  host_id; } ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_ALLOCATE_STREAM ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,struct sst_ipc_message*) ; 
 int /*<<< orphan*/  trace_hsw_stream_alloc_reply (struct sst_hsw_stream*) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int /*<<< orphan*/ ) ; 

int sst_hsw_stream_commit(struct sst_hsw *hsw, struct sst_hsw_stream *stream)
{
	struct sst_ipc_message request, reply = {0};
	int ret;

	if (!stream) {
		dev_warn(hsw->dev, "warning: stream is NULL, no stream to commit, ignore it.\n");
		return 0;
	}

	if (stream->commited) {
		dev_warn(hsw->dev, "warning: stream is already committed, ignore it.\n");
		return 0;
	}

	trace_ipc_request("stream alloc", stream->host_id);

	request.header = IPC_GLB_TYPE(IPC_GLB_ALLOCATE_STREAM);
	request.data = &stream->request;
	request.size = sizeof(stream->request);
	reply.data = &stream->reply;
	reply.size = sizeof(stream->reply);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, &reply);
	if (ret < 0) {
		dev_err(hsw->dev, "error: stream commit failed\n");
		return ret;
	}

	stream->commited = true;
	trace_hsw_stream_alloc_reply(stream);

	return 0;
}