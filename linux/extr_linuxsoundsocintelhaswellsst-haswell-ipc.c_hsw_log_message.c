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
typedef  scalar_t__ u32 ;
struct sst_hsw_log_stream {int /*<<< orphan*/  notify_work; int /*<<< orphan*/  rw_mutex; int /*<<< orphan*/  curr_pos; int /*<<< orphan*/  last_pos; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; int /*<<< orphan*/  dev; struct sst_hsw_log_stream log_stream; } ;

/* Variables and functions */
 scalar_t__ IPC_DEBUG_REQUEST_LOG_DUMP ; 
 scalar_t__ IPC_LOG_OP_MASK ; 
 scalar_t__ IPC_LOG_OP_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_dsp_inbox_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hsw_log_message(struct sst_hsw *hsw, u32 header)
{
	u32 operation = (header & IPC_LOG_OP_MASK) >>  IPC_LOG_OP_SHIFT;
	struct sst_hsw_log_stream *stream = &hsw->log_stream;
	int ret = 1;

	if (operation != IPC_DEBUG_REQUEST_LOG_DUMP) {
		dev_err(hsw->dev,
			"error: log msg not implemented 0x%8.8x\n", header);
		return 0;
	}

	mutex_lock(&stream->rw_mutex);
	stream->last_pos = stream->curr_pos;
	sst_dsp_inbox_read(
		hsw->dsp, &stream->curr_pos, sizeof(stream->curr_pos));
	mutex_unlock(&stream->rw_mutex);

	schedule_work(&stream->notify_work);

	return ret;
}