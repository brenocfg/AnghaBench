#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  area; } ;
struct TYPE_4__ {int (* prepare ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ;int stream_tag; int /*<<< orphan*/  (* cleanup ) (int /*<<< orphan*/ ,TYPE_2__*,int) ;} ;
struct sst_dsp {TYPE_2__ dmab; int /*<<< orphan*/  dev; TYPE_1__ dsp_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_ADSP_FW_STATUS ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCIDR ; 
 int CNL_ADSP_REG_HIPCIDR_BUSY ; 
 int /*<<< orphan*/  CNL_FW_ROM_INIT ; 
 int /*<<< orphan*/  CNL_FW_STS_MASK ; 
 int /*<<< orphan*/  CNL_INIT_TIMEOUT ; 
 int CNL_IPC_PURGE ; 
 int CNL_ROM_CTRL_DMA_ID ; 
 int EIO ; 
 int /*<<< orphan*/  SKL_DSP_CORE0_MASK ; 
 int /*<<< orphan*/  cnl_dsp_disable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int cnl_dsp_enable_core (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnl_ipc_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  cnl_ipc_op_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int sst_dsp_register_poll (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sst_dsp_shim_write (struct sst_dsp*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static int cnl_prepare_fw(struct sst_dsp *ctx, const void *fwdata, u32 fwsize)
{

	int ret, stream_tag;

	stream_tag = ctx->dsp_ops.prepare(ctx->dev, 0x40, fwsize, &ctx->dmab);
	if (stream_tag <= 0) {
		dev_err(ctx->dev, "dma prepare failed: 0%#x\n", stream_tag);
		return stream_tag;
	}

	ctx->dsp_ops.stream_tag = stream_tag;
	memcpy(ctx->dmab.area, fwdata, fwsize);

	/* purge FW request */
	sst_dsp_shim_write(ctx, CNL_ADSP_REG_HIPCIDR,
			   CNL_ADSP_REG_HIPCIDR_BUSY | (CNL_IPC_PURGE |
			   ((stream_tag - 1) << CNL_ROM_CTRL_DMA_ID)));

	ret = cnl_dsp_enable_core(ctx, SKL_DSP_CORE0_MASK);
	if (ret < 0) {
		dev_err(ctx->dev, "dsp boot core failed ret: %d\n", ret);
		ret = -EIO;
		goto base_fw_load_failed;
	}

	/* enable interrupt */
	cnl_ipc_int_enable(ctx);
	cnl_ipc_op_int_enable(ctx);

	ret = sst_dsp_register_poll(ctx, CNL_ADSP_FW_STATUS, CNL_FW_STS_MASK,
				    CNL_FW_ROM_INIT, CNL_INIT_TIMEOUT,
				    "rom load");
	if (ret < 0) {
		dev_err(ctx->dev, "rom init timeout, ret: %d\n", ret);
		goto base_fw_load_failed;
	}

	return 0;

base_fw_load_failed:
	ctx->dsp_ops.cleanup(ctx->dev, &ctx->dmab, stream_tag);
	cnl_dsp_disable_core(ctx, SKL_DSP_CORE0_MASK);

	return ret;
}