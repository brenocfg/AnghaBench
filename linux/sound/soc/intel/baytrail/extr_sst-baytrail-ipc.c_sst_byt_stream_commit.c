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
struct sst_ipc_message {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct sst_byt_stream {int commited; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/  str_id; } ;
struct sst_byt {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_IA_ALLOC_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_byt_header (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,struct sst_ipc_message*) ; 

int sst_byt_stream_commit(struct sst_byt *byt, struct sst_byt_stream *stream)
{
	struct sst_ipc_message request, reply = {0};
	int ret;

	request.header = sst_byt_header(IPC_IA_ALLOC_STREAM,
				sizeof(stream->request) + sizeof(u32),
				true, stream->str_id);
	request.data = &stream->request;
	request.size = sizeof(stream->request);
	reply.data = &stream->reply;
	reply.size = sizeof(stream->reply);

	ret = sst_ipc_tx_message_wait(&byt->ipc, request, &reply);
	if (ret < 0) {
		dev_err(byt->dev, "ipc: error stream commit failed\n");
		return ret;
	}

	stream->commited = true;

	return 0;
}