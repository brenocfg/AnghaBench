#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_ipc_message {int size; TYPE_2__* data; int /*<<< orphan*/  header; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_hw_id; } ;
struct sst_hsw_stream {int /*<<< orphan*/  node; int /*<<< orphan*/  notify_work; TYPE_2__ free_req; TYPE_1__ reply; int /*<<< orphan*/  host_id; int /*<<< orphan*/  commited; } ;
struct sst_hsw {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; struct sst_dsp* dsp; } ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IPC_GLB_FREE_STREAM ; 
 int /*<<< orphan*/  IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct sst_hsw_stream*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hsw_stream_free_req (struct sst_hsw_stream*,TYPE_2__*) ; 
 int /*<<< orphan*/  trace_ipc_request (char*,int /*<<< orphan*/ ) ; 

int sst_hsw_stream_free(struct sst_hsw *hsw, struct sst_hsw_stream *stream)
{
	struct sst_ipc_message request;
	int ret = 0;
	struct sst_dsp *sst = hsw->dsp;
	unsigned long flags;

	if (!stream) {
		dev_warn(hsw->dev, "warning: stream is NULL, no stream to free, ignore it.\n");
		return 0;
	}

	/* dont free DSP streams that are not commited */
	if (!stream->commited)
		goto out;

	trace_ipc_request("stream free", stream->host_id);

	stream->free_req.stream_id = stream->reply.stream_hw_id;
	request.header = IPC_GLB_TYPE(IPC_GLB_FREE_STREAM);
	request.data = &stream->free_req;
	request.size = sizeof(stream->free_req);

	ret = sst_ipc_tx_message_wait(&hsw->ipc, request, NULL);
	if (ret < 0) {
		dev_err(hsw->dev, "error: free stream %d failed\n",
			stream->free_req.stream_id);
		return -EAGAIN;
	}

	trace_hsw_stream_free_req(stream, &stream->free_req);

out:
	cancel_work_sync(&stream->notify_work);
	spin_lock_irqsave(&sst->spinlock, flags);
	list_del(&stream->node);
	kfree(stream);
	spin_unlock_irqrestore(&sst->spinlock, flags);

	return ret;
}