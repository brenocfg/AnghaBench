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
struct stream_info {scalar_t__ resume_status; scalar_t__ status; int /*<<< orphan*/  resume_prev; int /*<<< orphan*/  prev; } ;
struct sst_fw_save {int /*<<< orphan*/  ddr; int /*<<< orphan*/  iram; int /*<<< orphan*/  dram; int /*<<< orphan*/  sram; } ;
struct sst_block {int dummy; } ;
struct TYPE_6__ {int max_streams; } ;
struct intel_sst_drv {int /*<<< orphan*/  dev; struct stream_info* streams; TYPE_3__ info; TYPE_2__* pdata; TYPE_1__* ops; scalar_t__ ddr_base; scalar_t__ ddr_end; int /*<<< orphan*/  ddr; int /*<<< orphan*/  mailbox; scalar_t__ dram_base; scalar_t__ dram_end; int /*<<< orphan*/  dram; scalar_t__ iram_base; scalar_t__ iram_end; int /*<<< orphan*/  iram; struct sst_fw_save* fw_save; } ;
struct device {int dummy; } ;
struct TYPE_5__ {scalar_t__ streams_lost_on_suspend; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start ) (struct intel_sst_drv*) ;int /*<<< orphan*/  (* reset ) (struct intel_sst_drv*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_DWNL_ID ; 
 int /*<<< orphan*/  SST_FW_LOADING ; 
 int /*<<< orphan*/  SST_FW_RUNNING ; 
 scalar_t__ SST_MAILBOX_SIZE ; 
 scalar_t__ STREAM_UN_INIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct intel_sst_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct sst_fw_save*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy32_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sst_block* sst_create_block (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_free_block (struct intel_sst_drv*,struct sst_block*) ; 
 int /*<<< orphan*/  sst_realloc_stream (struct intel_sst_drv*,int) ; 
 int /*<<< orphan*/  sst_set_fw_state_locked (struct intel_sst_drv*,int /*<<< orphan*/ ) ; 
 int sst_wait_timeout (struct intel_sst_drv*,struct sst_block*) ; 
 int /*<<< orphan*/  stub1 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  stub2 (struct intel_sst_drv*) ; 

__attribute__((used)) static int intel_sst_resume(struct device *dev)
{
	struct intel_sst_drv *ctx = dev_get_drvdata(dev);
	struct sst_fw_save *fw_save = ctx->fw_save;
	struct sst_block *block;
	int i, ret = 0;

	if (!fw_save)
		return 0;

	sst_set_fw_state_locked(ctx, SST_FW_LOADING);

	/* we have to restore the memory saved */
	ctx->ops->reset(ctx);

	ctx->fw_save = NULL;

	memcpy32_toio(ctx->iram, fw_save->iram, ctx->iram_end - ctx->iram_base);
	memcpy32_toio(ctx->dram, fw_save->dram, ctx->dram_end - ctx->dram_base);
	memcpy32_toio(ctx->mailbox, fw_save->sram, SST_MAILBOX_SIZE);
	memcpy32_toio(ctx->ddr, fw_save->ddr, ctx->ddr_end - ctx->ddr_base);

	kvfree(fw_save->sram);
	kvfree(fw_save->dram);
	kvfree(fw_save->iram);
	kvfree(fw_save->ddr);
	kfree(fw_save);

	block = sst_create_block(ctx, 0, FW_DWNL_ID);
	if (block == NULL)
		return -ENOMEM;


	/* start and wait for ack */
	ctx->ops->start(ctx);
	ret = sst_wait_timeout(ctx, block);
	if (ret) {
		dev_err(ctx->dev, "fw download failed %d\n", ret);
		/* FW download failed due to timeout */
		ret = -EBUSY;

	} else {
		sst_set_fw_state_locked(ctx, SST_FW_RUNNING);
	}

	if (ctx->pdata->streams_lost_on_suspend) {
		for (i = 1; i <= ctx->info.max_streams; i++) {
			struct stream_info *stream = &ctx->streams[i];

			if (stream->resume_status != STREAM_UN_INIT) {
				dev_dbg(ctx->dev, "Re-allocing stream %d status %d prev %d\n",
					i, stream->resume_status,
					stream->resume_prev);
				sst_realloc_stream(ctx, i);
				stream->status = stream->resume_status;
				stream->prev = stream->resume_prev;
			}
		}
	}

	sst_free_block(ctx, block);
	return ret;
}