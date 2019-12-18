#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  (* cl_cleanup_controller ) (struct sst_dsp*) ;} ;
struct TYPE_7__ {TYPE_1__ ops; } ;
struct sst_dsp {TYPE_3__* fw; TYPE_2__ cl_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  fw_name; struct skl_dev* thread_context; } ;
struct skl_dev {int boot_complete; int fw_loaded; int /*<<< orphan*/  boot_wait; scalar_t__ is_first_boot; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SKL_ADSP_FW_BIN_HDR_OFFSET ; 
 int /*<<< orphan*/  SKL_ADSP_FW_STATUS ; 
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  SKL_FW_INIT ; 
 int SKL_INIT_TIMEOUT ; 
 int /*<<< orphan*/  SKL_IPC_BOOT_MSECS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_3__*) ; 
 int request_firmware (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skl_check_fw_status (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int skl_cldma_prepare (struct sst_dsp*) ; 
 int skl_dsp_boot (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_dsp_strip_extended_manifest (struct firmware*) ; 
 int /*<<< orphan*/  skl_ipc_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_ipc_op_int_enable (struct sst_dsp*) ; 
 int skl_transfer_firmware (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_skl_parse_uuids (struct sst_dsp*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_read (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sst_dsp*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_load_base_firmware(struct sst_dsp *ctx)
{
	int ret = 0, i;
	struct skl_dev *skl = ctx->thread_context;
	struct firmware stripped_fw;
	u32 reg;

	skl->boot_complete = false;
	init_waitqueue_head(&skl->boot_wait);

	if (ctx->fw == NULL) {
		ret = request_firmware(&ctx->fw, ctx->fw_name, ctx->dev);
		if (ret < 0) {
			dev_err(ctx->dev, "Request firmware failed %d\n", ret);
			return -EIO;
		}
	}

	/* prase uuids on first boot */
	if (skl->is_first_boot) {
		ret = snd_skl_parse_uuids(ctx, ctx->fw, SKL_ADSP_FW_BIN_HDR_OFFSET, 0);
		if (ret < 0) {
			dev_err(ctx->dev, "UUID parsing err: %d\n", ret);
			release_firmware(ctx->fw);
			skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
			return ret;
		}
	}

	/* check for extended manifest */
	stripped_fw.data = ctx->fw->data;
	stripped_fw.size = ctx->fw->size;

	skl_dsp_strip_extended_manifest(&stripped_fw);

	ret = skl_dsp_boot(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "Boot dsp core failed ret: %d\n", ret);
		goto skl_load_base_firmware_failed;
	}

	ret = skl_cldma_prepare(ctx);
	if (ret < 0) {
		dev_err(ctx->dev, "CL dma prepare failed : %d\n", ret);
		goto skl_load_base_firmware_failed;
	}

	/* enable Interrupt */
	skl_ipc_int_enable(ctx);
	skl_ipc_op_int_enable(ctx);

	/* check ROM Status */
	for (i = SKL_INIT_TIMEOUT; i > 0; --i) {
		if (skl_check_fw_status(ctx, SKL_FW_INIT)) {
			dev_dbg(ctx->dev,
				"ROM loaded, we can continue with FW loading\n");
			break;
		}
		mdelay(1);
	}
	if (!i) {
		reg = sst_dsp_shim_read(ctx, SKL_ADSP_FW_STATUS);
		dev_err(ctx->dev,
			"Timeout waiting for ROM init done, reg:0x%x\n", reg);
		ret = -EIO;
		goto transfer_firmware_failed;
	}

	ret = skl_transfer_firmware(ctx, stripped_fw.data, stripped_fw.size);
	if (ret < 0) {
		dev_err(ctx->dev, "Transfer firmware failed%d\n", ret);
		goto transfer_firmware_failed;
	} else {
		ret = wait_event_timeout(skl->boot_wait, skl->boot_complete,
					msecs_to_jiffies(SKL_IPC_BOOT_MSECS));
		if (ret == 0) {
			dev_err(ctx->dev, "DSP boot failed, FW Ready timed-out\n");
			ret = -EIO;
			goto transfer_firmware_failed;
		}

		dev_dbg(ctx->dev, "Download firmware successful%d\n", ret);
		skl->fw_loaded = true;
	}
	return 0;
transfer_firmware_failed:
	ctx->cl_dev.ops.cl_cleanup_controller(ctx);
skl_load_base_firmware_failed:
	skl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);
	release_firmware(ctx->fw);
	ctx->fw = NULL;
	return ret;
}