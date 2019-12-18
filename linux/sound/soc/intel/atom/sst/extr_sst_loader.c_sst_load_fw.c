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
struct sst_block {int dummy; } ;
struct intel_sst_drv {scalar_t__ sst_state; TYPE_1__* ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  qos; int /*<<< orphan*/  memcpy_list; int /*<<< orphan*/  fw_in_mem; } ;
struct TYPE_2__ {int (* reset ) (struct intel_sst_drv*) ;int (* start ) (struct intel_sst_drv*) ;int /*<<< orphan*/  (* restore_dsp_context ) () ;int /*<<< orphan*/  (* post_download ) (struct intel_sst_drv*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_DWNL_ID ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 scalar_t__ SST_FW_LOADING ; 
 scalar_t__ SST_FW_RUNNING ; 
 scalar_t__ SST_RESET ; 
 scalar_t__ SST_SHUTDOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_qos_update_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sst_block* sst_create_block (struct intel_sst_drv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_do_memcpy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_free_block (struct intel_sst_drv*,struct sst_block*) ; 
 int sst_request_fw (struct intel_sst_drv*) ; 
 int sst_wait_timeout (struct intel_sst_drv*,struct sst_block*) ; 
 int stub1 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  stub2 (struct intel_sst_drv*) ; 
 int stub3 (struct intel_sst_drv*) ; 
 int /*<<< orphan*/  stub4 () ; 

int sst_load_fw(struct intel_sst_drv *sst_drv_ctx)
{
	int ret_val = 0;
	struct sst_block *block;

	dev_dbg(sst_drv_ctx->dev, "sst_load_fw\n");

	if (sst_drv_ctx->sst_state !=  SST_RESET ||
			sst_drv_ctx->sst_state == SST_SHUTDOWN)
		return -EAGAIN;

	if (!sst_drv_ctx->fw_in_mem) {
		dev_dbg(sst_drv_ctx->dev, "sst: FW not in memory retry to download\n");
		ret_val = sst_request_fw(sst_drv_ctx);
		if (ret_val)
			return ret_val;
	}

	block = sst_create_block(sst_drv_ctx, 0, FW_DWNL_ID);
	if (block == NULL)
		return -ENOMEM;

	/* Prevent C-states beyond C6 */
	pm_qos_update_request(sst_drv_ctx->qos, 0);

	sst_drv_ctx->sst_state = SST_FW_LOADING;

	ret_val = sst_drv_ctx->ops->reset(sst_drv_ctx);
	if (ret_val)
		goto restore;

	sst_do_memcpy(&sst_drv_ctx->memcpy_list);

	/* Write the DRAM/DCCM config before enabling FW */
	if (sst_drv_ctx->ops->post_download)
		sst_drv_ctx->ops->post_download(sst_drv_ctx);

	/* bring sst out of reset */
	ret_val = sst_drv_ctx->ops->start(sst_drv_ctx);
	if (ret_val)
		goto restore;

	ret_val = sst_wait_timeout(sst_drv_ctx, block);
	if (ret_val) {
		dev_err(sst_drv_ctx->dev, "fw download failed %d\n" , ret_val);
		/* FW download failed due to timeout */
		ret_val = -EBUSY;

	}


restore:
	/* Re-enable Deeper C-states beyond C6 */
	pm_qos_update_request(sst_drv_ctx->qos, PM_QOS_DEFAULT_VALUE);
	sst_free_block(sst_drv_ctx, block);
	dev_dbg(sst_drv_ctx->dev, "fw load successful!!!\n");

	if (sst_drv_ctx->ops->restore_dsp_context)
		sst_drv_ctx->ops->restore_dsp_context();
	sst_drv_ctx->sst_state = SST_FW_RUNNING;
	return ret_val;
}