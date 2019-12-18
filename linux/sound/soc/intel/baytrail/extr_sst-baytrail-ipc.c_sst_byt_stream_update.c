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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sst_byt_stream {int running; } ;
struct sst_byt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  header; } ;
struct ipc_message {TYPE_1__ tx; } ;

/* Variables and functions */
#define  IPC_IA_DROP_STREAM 132 
#define  IPC_IA_FREE_STREAM 131 
#define  IPC_IA_PAUSE_STREAM 130 
#define  IPC_IA_RESUME_STREAM 129 
#define  IPC_IA_START_STREAM 128 
 struct sst_byt_stream* sst_byt_get_stream (struct sst_byt*,int) ; 
 int sst_byt_header_msg_id (int /*<<< orphan*/ ) ; 
 int sst_byt_header_str_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sst_byt_stream_update(struct sst_byt *byt, struct ipc_message *msg)
{
	struct sst_byt_stream *stream;
	u64 header = msg->tx.header;
	u8 stream_id = sst_byt_header_str_id(header);
	u8 stream_msg = sst_byt_header_msg_id(header);

	stream = sst_byt_get_stream(byt, stream_id);
	if (stream == NULL)
		return;

	switch (stream_msg) {
	case IPC_IA_DROP_STREAM:
	case IPC_IA_PAUSE_STREAM:
	case IPC_IA_FREE_STREAM:
		stream->running = false;
		break;
	case IPC_IA_START_STREAM:
	case IPC_IA_RESUME_STREAM:
		stream->running = true;
		break;
	}
}