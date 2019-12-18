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
typedef  int u32 ;
struct sst_hsw_stream {int header; int /*<<< orphan*/  notify_work; } ;
struct sst_hsw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  IPC_STR_NOTIFICATION 129 
#define  IPC_STR_STAGE_MESSAGE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct sst_hsw_stream* get_stream_by_id (struct sst_hsw*,int) ; 
 int hsw_process_reply (struct sst_hsw*,int) ; 
 int msg_get_stream_id (int) ; 
 int msg_get_stream_type (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hsw_stream_message(struct sst_hsw *hsw, u32 header)
{
	u32 stream_msg, stream_id;
	struct sst_hsw_stream *stream;
	int handled = 0;

	stream_msg = msg_get_stream_type(header);
	stream_id = msg_get_stream_id(header);

	stream = get_stream_by_id(hsw, stream_id);
	if (stream == NULL)
		return handled;

	stream->header = header;

	switch (stream_msg) {
	case IPC_STR_STAGE_MESSAGE:
		dev_err(hsw->dev, "error: stage msg not implemented 0x%8.8x\n",
			header);
		break;
	case IPC_STR_NOTIFICATION:
		schedule_work(&stream->notify_work);
		break;
	default:
		/* handle pending message complete request */
		handled = hsw_process_reply(hsw, header);
		break;
	}

	return handled;
}