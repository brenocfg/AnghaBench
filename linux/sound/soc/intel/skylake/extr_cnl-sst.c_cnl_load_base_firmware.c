#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sst_dsp {TYPE_1__* fw; int /*<<< orphan*/  dev; int /*<<< orphan*/  fw_name; struct skl_dev* thread_context; } ;
struct skl_dev {int fw_loaded; int /*<<< orphan*/  boot_complete; int /*<<< orphan*/  boot_wait; scalar_t__ is_first_boot; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_ADSP_FW_HDR_OFFSET ; 
 int EIO ; 
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  SKL_IPC_BOOT_MSECS ; 
 int /*<<< orphan*/  cnl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int cnl_prepare_fw (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int request_firmware (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dsp_strip_extended_manifest (struct firmware*) ; 
 int snd_skl_parse_uuids (struct sst_dsp*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_transfer_fw_host_dma (struct sst_dsp*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnl_load_base_firmware(struct sst_dsp *ctx)
{
	struct firmware stripped_fw;
	struct skl_dev *cnl = ctx->thread_context;
	int ret;

	if (!ctx->fw) {
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		if (ret < 0) {
			dev_err(ctx->dev, "request firmware failed: %d\n", ret);
			goto cnl_load_base_firmware_failed;
		}
	}

	/* parse uuids if first boot */
	if (cnl->is_first_boot) {
		ret = snd_skl_parse_uuids(ctx, ctx->fw,
					  CNL_ADSP_FW_HDR_OFFSET, 0);
		if (ret < 0)
			goto cnl_load_base_firmware_failed;
	}

	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;
	skl_dsp_strip_extended_manifest(&stripped_fw);

	ret = cnl_prepare_fw(ctx, stripped_fw.data, stripped_fw.size);
	if (ret < 0) {
		dev_err(ctx->dev, "prepare firmware failed: %d\n", ret);
		goto cnl_load_base_firmware_failed;
	}

	ret = sst_transfer_fw_host_dma(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "transfer firmware failed: %d\n", ret);
		cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		goto cnl_load_base_firmware_failed;
	}

	ret = wait_event_timeout(cnl->boot_wait, cnl->boot_complete,
				 msecs_to_jiffies(SKL_IPC_BOOT_MSECS));
	if (ret == 0) {
		dev_err(ctx->dev, "FW ready timed-out\n");
		cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
		ret = -EIO;
		goto cnl_load_base_firmware_failed;
	}

	cnl->fw_loaded = true;

	return 0;

cnl_load_base_firmware_failed:
	release_firmware(ctx->fw);
	ctx->fw = NULL;

	return ret;
}