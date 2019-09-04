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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sst_byt_alloc_response {int dummy; } ;
struct sst_byt_alloc_params {int dummy; } ;
struct sst_byt_stream {int commited; int /*<<< orphan*/  str_id; struct sst_byt_alloc_response reply; struct sst_byt_alloc_params request; } ;
struct sst_byt {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_IA_ALLOC_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_byt_header (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sst_byt_alloc_params*,int,struct sst_byt_alloc_response*,int) ; 

int sst_byt_stream_commit(struct sst_byt *byt, struct sst_byt_stream *stream)
{
	struct sst_byt_alloc_params *str_req = &stream->request;
	struct sst_byt_alloc_response *reply = &stream->reply;
	u64 header;
	int ret;

	header = sst_byt_header(IPC_IA_ALLOC_STREAM,
				sizeof(*str_req) + sizeof(u32),
				true, stream->str_id);
	ret = sst_ipc_tx_message_wait(&byt->ipc, header, str_req,
				      sizeof(*str_req),
				      reply, sizeof(*reply));
	if (ret < 0) {
		dev_err(byt->dev, "ipc: error stream commit failed\n");
		return ret;
	}

	stream->commited = true;

	return 0;
}