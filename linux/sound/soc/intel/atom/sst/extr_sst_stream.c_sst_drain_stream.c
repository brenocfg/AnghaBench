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
typedef  int /*<<< orphan*/  u8 ;
struct stream_info {scalar_t__ status; int /*<<< orphan*/  pipe_id; int /*<<< orphan*/  task_id; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBADRQC ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPC_CMD ; 
 int /*<<< orphan*/  IPC_IA_DRAIN_STREAM_MRFLD ; 
 scalar_t__ STREAM_INIT ; 
 scalar_t__ STREAM_PAUSED ; 
 scalar_t__ STREAM_RUNNING ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,int) ; 
 int sst_prepare_and_post_msg (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int,int,int,int) ; 

int sst_drain_stream(struct intel_sst_drv *sst_drv_ctx,
			int str_id, bool partial_drain)
{
	int retval = 0;
	struct stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_drain_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	if (!str_info)
		return -EINVAL;
	if (str_info->status != STREAM_RUNNING &&
		str_info->status != STREAM_INIT &&
		str_info->status != STREAM_PAUSED) {
			dev_err(sst_drv_ctx->dev, "SST ERR: BADQRC for stream = %d\n",
				       str_info->status);
			return -EBADRQC;
	}

	retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id, IPC_CMD,
			IPC_IA_DRAIN_STREAM_MRFLD, str_info->pipe_id,
			sizeof(u8), &partial_drain, NULL, true, true, false, false);
	/*
	 * with new non blocked drain implementation in core we dont need to
	 * wait for respsonse, and need to only invoke callback for drain
	 * complete
	 */

	return retval;
}