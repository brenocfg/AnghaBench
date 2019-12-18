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
struct sst_ipc_message {int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
struct sst_byt_stream {int commited; int /*<<< orphan*/  node; int /*<<< orphan*/  str_id; } ;
struct sst_byt {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; struct sst_dsp* dsp; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IPC_IA_FREE_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sst_byt_stream*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sst_byt_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 

int sst_byt_stream_free(struct sst_byt *byt, struct sst_byt_stream *stream)
{
	struct sst_ipc_message request = {0};
	int ret = 0;
	struct sst_dsp *sst = byt->dsp;
	unsigned long flags;

	if (!stream->commited)
		goto out;

	request.header = sst_byt_header(IPC_IA_FREE_STREAM,
			0, false, stream->str_id);
	ret = sst_ipc_tx_message_wait(&byt->ipc, request, NULL);
	if (ret < 0) {
		dev_err(byt->dev, "ipc: free stream %d failed\n",
			stream->str_id);
		return -EAGAIN;
	}

	stream->commited = false;
out:
	spin_lock_irqsave(&sst->spinlock, flags);
	list_del(&stream->node);
	kfree(stream);
	spin_unlock_irqrestore(&sst->spinlock, flags);

	return ret;
}