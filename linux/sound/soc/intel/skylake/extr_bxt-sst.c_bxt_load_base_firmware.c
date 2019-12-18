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
 int /*<<< orphan*/  BXT_ADSP_ERROR_CODE ; 
 int /*<<< orphan*/  BXT_ADSP_FW_BIN_HDR_OFFSET ; 
 int /*<<< orphan*/  BXT_ADSP_FW_STATUS ; 
 int BXT_FW_ROM_INIT_RETRY ; 
 int EIO ; 
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  SKL_IPC_BOOT_MSECS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int request_firmware (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dsp_strip_extended_manifest (struct firmware*) ; 
 int snd_skl_parse_uuids (struct sst_dsp*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sst_bxt_prepare_fw (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_read (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int sst_transfer_fw_host_dma (struct sst_dsp*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bxt_load_base_firmware(struct sst_dsp *ctx)
{
	struct firmware stripped_fw;
	struct skl_dev *skl = ctx->thread_context;
	int ret, i;

	if (ctx->fw == NULL) {
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		if (ret < 0) {
			dev_err(ctx->dev, "Request firmware failed %d\n", ret);
			return ret;
		}
	}

	/* prase uuids on first boot */
	if (skl->is_first_boot) {
		ret = snd_skl_parse_uuids(ctx, ctx->fw, BXT_ADSP_FW_BIN_HDR_OFFSET, 0);
		if (ret < 0)
			goto sst_load_base_firmware_failed;
	}

	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;
	skl_dsp_strip_extended_manifest(&stripped_fw);


	for (i = 0; i < BXT_FW_ROM_INIT_RETRY; i++) {
		ret = sst_bxt_prepare_fw(ctx, stripped_fw.data, stripped_fw.size);
		if (ret == 0)
			break;
	}

	if (ret < 0) {
		dev_err(ctx->dev, "Error code=0x%x: FW status=0x%x\n",
			sst_dsp_shim_read(ctx, BXT_ADSP_ERROR_CODE),
			sst_dsp_shim_read(ctx, BXT_ADSP_FW_STATUS));

		dev_err(ctx->dev, "Core En/ROM load fail:%d\n", ret);
		goto sst_load_base_firmware_failed;
	}

	ret = sst_transfer_fw_host_dma(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "Transfer firmware failed %d\n", ret);
		dev_info(ctx->dev, "Error code=0x%x: FW status=0x%x\n",
			sst_dsp_shim_read(ctx, BXT_ADSP_ERROR_CODE),
			sst_dsp_shim_read(ctx, BXT_ADSP_FW_STATUS));

		skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
	} else {
		dev_dbg(ctx->dev, "Firmware download successful\n");
		ret = wait_event_timeout(skl->boot_wait, skl->boot_complete,
					msecs_to_jiffies(SKL_IPC_BOOT_MSECS));
		if (ret == 0) {
			dev_err(ctx->dev, "DSP boot fail, FW Ready timeout\n");
			skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
			ret = -EIO;
		} else {
			ret = 0;
			skl->fw_loaded = true;
		}
	}

	return ret;

sst_load_base_firmware_failed:
	release_firmware(ctx->fw);
	ctx->fw = NULL;
	return ret;
}