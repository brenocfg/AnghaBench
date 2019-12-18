#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stream_info {scalar_t__ status; scalar_t__ resume_status; int /*<<< orphan*/  prev; int /*<<< orphan*/  resume_prev; } ;
struct sst_fw_save {void* iram; void* dram; void* sram; void* ddr; } ;
struct TYPE_4__ {int max_streams; } ;
struct intel_sst_drv {scalar_t__ sst_state; TYPE_3__* ops; struct sst_fw_save* fw_save; scalar_t__ ddr_base; scalar_t__ ddr_end; int /*<<< orphan*/  ddr; int /*<<< orphan*/  mailbox; scalar_t__ dram_base; scalar_t__ dram_end; int /*<<< orphan*/  dram; scalar_t__ iram_base; scalar_t__ iram_end; int /*<<< orphan*/  iram; int /*<<< orphan*/  post_msg_wq; int /*<<< orphan*/  irq_num; TYPE_2__* pdata; struct stream_info* streams; TYPE_1__ info; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* reset ) (struct intel_sst_drv*) ;scalar_t__ (* save_dsp_context ) (struct intel_sst_drv*) ;} ;
struct TYPE_5__ {scalar_t__ streams_lost_on_suspend; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SST_MAILBOX_SIZE ; 
 scalar_t__ SST_RESET ; 
 scalar_t__ STREAM_RUNNING ; 
 scalar_t__ STREAM_UN_INIT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sst_fw_save*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 void* kvzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sst_fw_save* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy32_fromio (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sst_free_stream (struct intel_sst_drv*,int) ; 
 int /*<<< orphan*/  sst_set_fw_state_locked (struct intel_sst_drv*,scalar_t__) ; 
 scalar_t__ stub1 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  stub2 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_sst_suspend(struct device *dev)
{
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);
	struct sst_fw_save *fw_save;
	int i, ret = 0;

	/* check first if we are already in SW reset */
	if (ctx->sst_state == SST_RESET)
		return 0;

	/*
	 * check if any stream is active and running
	 * they should already by suspend by soc_suspend
	 */
	for (i = 1; i <= ctx->info.max_streams; i++) {
		struct stream_info *stream = &ctx->streams[i];

		if (stream->status == STREAM_RUNNING) {
			dev_err(dev, "stream %d is running, can't suspend, abort\n", i);
			return -EBUSY;
		}

		if (ctx->pdata->streams_lost_on_suspend) {
			stream->resume_status = stream->status;
			stream->resume_prev = stream->prev;
			if (stream->status != STREAM_UN_INIT)
				sst_free_stream(ctx, i);
		}
	}
	synchronize_irq(ctx->irq_num);
	flush_workqueue(ctx->post_msg_wq);

	/* Move the SST state to Reset */
	sst_set_fw_state_locked(ctx, SST_RESET);

	/* tell DSP we are suspending */
	if (ctx->ops->save_dsp_context(ctx))
		return -EBUSY;

	/* save the memories */
	fw_save = kzalloc(sizeof(*fw_save), GFP_KERNEL);
	if (!fw_save)
		return -ENOMEM;
	fw_save->iram = kvzalloc(ctx->iram_end - ctx->iram_base, GFP_KERNEL);
	if (!fw_save->iram) {
		ret = -ENOMEM;
		goto iram;
	}
	fw_save->dram = kvzalloc(ctx->dram_end - ctx->dram_base, GFP_KERNEL);
	if (!fw_save->dram) {
		ret = -ENOMEM;
		goto dram;
	}
	fw_save->sram = kvzalloc(SST_MAILBOX_SIZE, GFP_KERNEL);
	if (!fw_save->sram) {
		ret = -ENOMEM;
		goto sram;
	}

	fw_save->ddr = kvzalloc(ctx->ddr_end - ctx->ddr_base, GFP_KERNEL);
	if (!fw_save->ddr) {
		ret = -ENOMEM;
		goto ddr;
	}

	memcpy32_fromio(fw_save->iram, ctx->iram, ctx->iram_end - ctx->iram_base);
	memcpy32_fromio(fw_save->dram, ctx->dram, ctx->dram_end - ctx->dram_base);
	memcpy32_fromio(fw_save->sram, ctx->mailbox, SST_MAILBOX_SIZE);
	memcpy32_fromio(fw_save->ddr, ctx->ddr, ctx->ddr_end - ctx->ddr_base);

	ctx->fw_save = fw_save;
	ctx->ops->reset(ctx);
	return 0;
ddr:
	kvfree(fw_save->sram);
sram:
	kvfree(fw_save->dram);
dram:
	kvfree(fw_save->iram);
iram:
	kfree(fw_save);
	return ret;
}