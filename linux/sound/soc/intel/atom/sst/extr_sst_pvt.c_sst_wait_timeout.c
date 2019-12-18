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
struct sst_block {int condition; int ret_code; int on; int /*<<< orphan*/  msg_id; int /*<<< orphan*/  drv_id; } ;
struct intel_sst_drv {int /*<<< orphan*/  sst_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SST_BLOCK_TIMEOUT ; 
 int /*<<< orphan*/  SST_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int sst_wait_timeout(struct intel_sst_drv *sst_drv_ctx, struct sst_block *block)
{
	int retval = 0;

	/*
	 * NOTE:
	 * Observed that FW processes the alloc msg and replies even
	 * before the alloc thread has finished execution
	 */
	dev_dbg(sst_drv_ctx->dev,
		"waiting for condition %x ipc %d drv_id %d\n",
		block->condition, block->msg_id, block->drv_id);
	if (wait_event_timeout(sst_drv_ctx->wait_queue,
				block->condition,
				msecs_to_jiffies(SST_BLOCK_TIMEOUT))) {
		/* event wake */
		dev_dbg(sst_drv_ctx->dev, "Event wake %x\n",
				block->condition);
		dev_dbg(sst_drv_ctx->dev, "message ret: %d\n",
				block->ret_code);
		retval = -block->ret_code;
	} else {
		block->on = false;
		dev_err(sst_drv_ctx->dev,
			"Wait timed-out condition:%#x, msg_id:%#x fw_state %#x\n",
			block->condition, block->msg_id, sst_drv_ctx->sst_state);
		sst_drv_ctx->sst_state = SST_RESET;

		retval = -EBUSY;
	}
	return retval;
}