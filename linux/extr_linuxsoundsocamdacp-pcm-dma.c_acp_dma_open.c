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
struct snd_pcm_runtime {struct audio_substream_data* private_data; int /*<<< orphan*/  hw; } ;
struct audio_substream_data {int /*<<< orphan*/  acp_mmio; } ;
struct audio_drv_data {int asic_type; int /*<<< orphan*/  acp_mmio; int /*<<< orphan*/  capture_i2sbt_stream; int /*<<< orphan*/  play_i2sbt_stream; int /*<<< orphan*/  capture_i2ssp_stream; int /*<<< orphan*/  play_i2ssp_stream; } ;

/* Variables and functions */
#define  CHIP_STONEY 128 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  acp_pcm_hardware_capture ; 
 int /*<<< orphan*/  acp_pcm_hardware_playback ; 
 int /*<<< orphan*/  acp_reg_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acp_set_sram_bank_state (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  acp_st_pcm_hardware_capture ; 
 int /*<<< orphan*/  acp_st_pcm_hardware_playback ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct audio_drv_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct audio_substream_data*) ; 
 struct audio_substream_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmACP_EXTERNAL_INTR_ENB ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acp_dma_open(struct snd_pcm_substream *substream)
{
	u16 bank;
	int ret = 0;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *prtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(prtd,
								    DRV_NAME);
	struct audio_drv_data *intr_data = dev_get_drvdata(component->dev);
	struct audio_substream_data *adata =
		kzalloc(sizeof(struct audio_substream_data), GFP_KERNEL);
	if (!adata)
		return -ENOMEM;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		switch (intr_data->asic_type) {
		case CHIP_STONEY:
			runtime->hw = acp_st_pcm_hardware_playback;
			break;
		default:
			runtime->hw = acp_pcm_hardware_playback;
		}
	} else {
		switch (intr_data->asic_type) {
		case CHIP_STONEY:
			runtime->hw = acp_st_pcm_hardware_capture;
			break;
		default:
			runtime->hw = acp_pcm_hardware_capture;
		}
	}

	ret = snd_pcm_hw_constraint_integer(runtime,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	if (ret < 0) {
		dev_err(component->dev, "set integer constraint failed\n");
		kfree(adata);
		return ret;
	}

	adata->acp_mmio = intr_data->acp_mmio;
	runtime->private_data = adata;

	/*
	 * Enable ACP irq, when neither playback or capture streams are
	 * active by the time when a new stream is being opened.
	 * This enablement is not required for another stream, if current
	 * stream is not closed
	 */
	if (!intr_data->play_i2ssp_stream && !intr_data->capture_i2ssp_stream &&
	    !intr_data->play_i2sbt_stream && !intr_data->capture_i2sbt_stream)
		acp_reg_write(1, adata->acp_mmio, mmACP_EXTERNAL_INTR_ENB);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		/*
		 * For Stoney, Memory gating is disabled,i.e SRAM Banks
		 * won't be turned off. The default state for SRAM banks is ON.
		 * Setting SRAM bank state code skipped for STONEY platform.
		 */
		if (intr_data->asic_type != CHIP_STONEY) {
			for (bank = 1; bank <= 4; bank++)
				acp_set_sram_bank_state(intr_data->acp_mmio,
							bank, true);
		}
	} else {
		if (intr_data->asic_type != CHIP_STONEY) {
			for (bank = 5; bank <= 8; bank++)
				acp_set_sram_bank_state(intr_data->acp_mmio,
							bank, true);
		}
	}

	return 0;
}