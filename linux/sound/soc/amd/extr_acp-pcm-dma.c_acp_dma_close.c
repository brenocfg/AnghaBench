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
typedef  int u16 ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct audio_substream_data* private_data; } ;
struct audio_substream_data {int i2s_instance; } ;
struct audio_drv_data {int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/ * capture_i2sbt_stream; int /*<<< orphan*/ * play_i2sbt_stream; int /*<<< orphan*/ * capture_i2ssp_stream; int /*<<< orphan*/ * play_i2ssp_stream; int /*<<< orphan*/  asic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_STONEY ; 
 int /*<<< orphan*/  DRV_NAME ; 
#define  I2S_BT_INSTANCE 129 
#define  I2S_SP_INSTANCE 128 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  acp_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_set_sram_bank_state (int /*<<< orphan*/ ,int,int) ; 
 struct audio_drv_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct audio_substream_data*) ; 
 int /*<<< orphan*/  mmACP_EXTERNAL_INTR_ENB ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp_dma_close(struct snd_pcm_substream *substream)
{
	u16 bank;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct audio_substream_data *rtd = runtime->private_data;
	struct snd_soc_pcm_runtime *prtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(prtd,
								    DRV_NAME);
	struct audio_drv_data *adata = dev_get_drvdata(component->dev);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (rtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			adata->play_i2sbt_stream = NULL;
			break;
		case I2S_SP_INSTANCE:
		default:
			adata->play_i2ssp_stream = NULL;
			/*
			 * For Stoney, Memory gating is disabled,i.e SRAM Banks
			 * won't be turned off. The default state for SRAM banks
			 * is ON.Setting SRAM bank state code skipped for STONEY
			 * platform. Added condition checks for Carrizo platform
			 * only.
			 */
			if (adata->asic_type != CHIP_STONEY) {
				for (bank = 1; bank <= 4; bank++)
					acp_set_sram_bank_state(adata->acp_mmio,
								bank, false);
			}
		}
	} else  {
		switch (rtd->i2s_instance) {
		case I2S_BT_INSTANCE:
			adata->capture_i2sbt_stream = NULL;
			break;
		case I2S_SP_INSTANCE:
		default:
			adata->capture_i2ssp_stream = NULL;
			if (adata->asic_type != CHIP_STONEY) {
				for (bank = 5; bank <= 8; bank++)
					acp_set_sram_bank_state(adata->acp_mmio,
								bank, false);
			}
		}
	}

	/*
	 * Disable ACP irq, when the current stream is being closed and
	 * another stream is also not active.
	 */
	if (!adata->play_i2ssp_stream && !adata->capture_i2ssp_stream &&
	    !adata->play_i2sbt_stream && !adata->capture_i2sbt_stream)
		acp_reg_write(0, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);
	kfree(rtd);
	return 0;
}