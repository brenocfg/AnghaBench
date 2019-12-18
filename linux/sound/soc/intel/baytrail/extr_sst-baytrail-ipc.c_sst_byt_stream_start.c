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
struct sst_ipc_message {int size; struct sst_byt_start_stream_params* data; int /*<<< orphan*/  header; } ;
struct sst_byt_stream {int /*<<< orphan*/  str_id; } ;
struct sst_byt_start_stream_params {int /*<<< orphan*/  byte_offset; } ;
struct sst_byt {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc; } ;
typedef  int /*<<< orphan*/  start_stream ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_IA_START_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_byt_header (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_nowait (int /*<<< orphan*/ *,struct sst_ipc_message) ; 

int sst_byt_stream_start(struct sst_byt *byt, struct sst_byt_stream *stream,
			 u32 start_offset)
{
	struct sst_byt_start_stream_params start_stream;
	struct sst_ipc_message request;
	int ret;

	start_stream.byte_offset = start_offset;
	request.header = sst_byt_header(IPC_IA_START_STREAM,
				sizeof(start_stream) + sizeof(u32),
				true, stream->str_id);
	request.data = &start_stream;
	request.size = sizeof(start_stream);

	ret = sst_ipc_tx_message_nowait(&byt->ipc, request);
	if (ret < 0)
		dev_err(byt->dev, "ipc: error failed to start stream %d\n",
			stream->str_id);

	return ret;
}