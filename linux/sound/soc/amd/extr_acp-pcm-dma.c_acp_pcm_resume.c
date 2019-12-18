#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct device {int dummy; } ;
struct audio_substream_data {int dummy; } ;
struct audio_drv_data {scalar_t__ asic_type; int /*<<< orphan*/  acp_mmio; TYPE_8__* capture_i2sbt_stream; TYPE_6__* play_i2sbt_stream; TYPE_4__* capture_i2ssp_stream; TYPE_2__* play_i2ssp_stream; } ;
struct TYPE_16__ {TYPE_7__* runtime; } ;
struct TYPE_15__ {struct audio_substream_data* private_data; } ;
struct TYPE_14__ {TYPE_5__* runtime; } ;
struct TYPE_13__ {struct audio_substream_data* private_data; } ;
struct TYPE_12__ {TYPE_3__* runtime; } ;
struct TYPE_11__ {struct audio_substream_data* private_data; } ;
struct TYPE_10__ {TYPE_1__* runtime; } ;
struct TYPE_9__ {struct audio_substream_data* private_data; } ;

/* Variables and functions */
 scalar_t__ CHIP_CARRIZO ; 
 scalar_t__ CHIP_STONEY ; 
 int acp_init (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  acp_reg_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_set_sram_bank_state (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  config_acp_dma (int /*<<< orphan*/ ,struct audio_substream_data*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct audio_drv_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mmACP_EXTERNAL_INTR_ENB ; 

__attribute__((used)) static int acp_pcm_resume(struct device *dev)
{
	u16 bank;
	int status;
	struct audio_substream_data *rtd;
	struct audio_drv_data *adata = dev_get_drvdata(dev);

	status = acp_init(adata->acp_mmio, adata->asic_type);
	if (status) {
		dev_err(dev, "ACP Init failed status:%d\n", status);
		return status;
	}

	if (adata->play_i2ssp_stream && adata->play_i2ssp_stream->runtime) {
		/*
		 * For Stoney, Memory gating is disabled,i.e SRAM Banks
		 * won't be turned off. The default state for SRAM banks is ON.
		 * Setting SRAM bank state code skipped for STONEY platform.
		 */
		if (adata->asic_type != CHIP_STONEY) {
			for (bank = 1; bank <= 4; bank++)
				acp_set_sram_bank_state(adata->acp_mmio, bank,
							true);
		}
		rtd = adata->play_i2ssp_stream->runtime->private_data;
		config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
	}
	if (adata->capture_i2ssp_stream &&
	    adata->capture_i2ssp_stream->runtime) {
		if (adata->asic_type != CHIP_STONEY) {
			for (bank = 5; bank <= 8; bank++)
				acp_set_sram_bank_state(adata->acp_mmio, bank,
							true);
		}
		rtd =  adata->capture_i2ssp_stream->runtime->private_data;
		config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
	}
	if (adata->asic_type != CHIP_CARRIZO) {
		if (adata->play_i2sbt_stream &&
		    adata->play_i2sbt_stream->runtime) {
			rtd = adata->play_i2sbt_stream->runtime->private_data;
			config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
		}
		if (adata->capture_i2sbt_stream &&
		    adata->capture_i2sbt_stream->runtime) {
			rtd = adata->capture_i2sbt_stream->runtime->private_data;
			config_acp_dma(adata->acp_mmio, rtd, adata->asic_type);
		}
	}
	acp_reg_write(1, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	return 0;
}