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
struct sst_block {scalar_t__ ret_code; int /*<<< orphan*/  condition; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sst_wait_interruptible(struct intel_sst_drv *sst_drv_ctx,
				struct sst_block *block)
{
	int retval = 0;

	if (!wait_event_interruptible(sst_drv_ctx->wait_queue,
				block->condition)) {
		/* event wake */
		if (block->ret_code < 0) {
			dev_err(sst_drv_ctx->dev,
				"stream failed %d\n", block->ret_code);
			retval = -EBUSY;
		} else {
			dev_dbg(sst_drv_ctx->dev, "event up\n");
			retval = 0;
		}
	} else {
		dev_err(sst_drv_ctx->dev, "signal interrupted\n");
		retval = -EINTR;
	}
	return retval;

}