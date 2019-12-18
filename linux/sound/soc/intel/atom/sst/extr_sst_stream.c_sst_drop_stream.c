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
struct stream_info {int status; int prev; int /*<<< orphan*/  pipe_id; int /*<<< orphan*/  task_id; scalar_t__ cumm_bytes; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBADRQC ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPC_CMD ; 
 int /*<<< orphan*/  IPC_IA_DROP_STREAM_MRFLD ; 
 int STREAM_INIT ; 
 int STREAM_UN_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct stream_info* get_stream_info (struct intel_sst_drv*,int) ; 
 int sst_prepare_and_post_msg (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 

int sst_drop_stream(struct intel_sst_drv *sst_drv_ctx, int str_id)
{
	int retval = 0;
	struct stream_info *str_info;

	dev_dbg(sst_drv_ctx->dev, "SST DBG:sst_drop_stream for %d\n", str_id);
	str_info = get_stream_info(sst_drv_ctx, str_id);
	if (!str_info)
		return -EINVAL;

	if (str_info->status != STREAM_UN_INIT) {
		str_info->prev = STREAM_UN_INIT;
		str_info->status = STREAM_INIT;
		str_info->cumm_bytes = 0;
		retval = sst_prepare_and_post_msg(sst_drv_ctx, str_info->task_id,
				IPC_CMD, IPC_IA_DROP_STREAM_MRFLD,
				str_info->pipe_id, 0, NULL, NULL,
				true, true, true, false);
	} else {
		retval = -EBADRQC;
		dev_dbg(sst_drv_ctx->dev, "BADQRC for stream, state %x\n",
				str_info->status);
	}
	return retval;
}