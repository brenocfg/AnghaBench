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
struct intel_sst_drv {scalar_t__ sst_state; TYPE_1__* ops; int /*<<< orphan*/  post_msg_wq; int /*<<< orphan*/  irq_num; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct intel_sst_drv*) ;scalar_t__ (* save_dsp_context ) (struct intel_sst_drv*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ SST_RESET ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_set_fw_state_locked (struct intel_sst_drv*,scalar_t__) ; 
 scalar_t__ stub1 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  stub2 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_sst_runtime_suspend(struct device *dev)
{
	int ret = 0;
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);

	if (ctx->sst_state == SST_RESET) {
		dev_dbg(dev, "LPE is already in RESET state, No action\n");
		return 0;
	}
	/* save fw context */
	if (ctx->ops->save_dsp_context(ctx))
		return -EBUSY;

	/* Move the SST state to Reset */
	sst_set_fw_state_locked(ctx, SST_RESET);

	synchronize_irq(ctx->irq_num);
	flush_workqueue(ctx->post_msg_wq);

	ctx->ops->reset(ctx);

	return ret;
}