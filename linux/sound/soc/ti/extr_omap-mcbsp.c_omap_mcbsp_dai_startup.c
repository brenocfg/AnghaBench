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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct omap_mcbsp {TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  omap_mcbsp_hwrule_min_buffersize ; 
 int omap_mcbsp_request (struct omap_mcbsp*) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct omap_mcbsp*,int /*<<< orphan*/ ,int) ; 
 struct omap_mcbsp* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int omap_mcbsp_dai_startup(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *cpu_dai)
{
	struct omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	int err = 0;

	if (!cpu_dai->active)
		err = omap_mcbsp_request(mcbsp);

	/*
	 * OMAP3 McBSP FIFO is word structured.
	 * McBSP2 has 1024 + 256 = 1280 word long buffer,
	 * McBSP1,3,4,5 has 128 word long buffer
	 * This means that the size of the FIFO depends on the sample format.
	 * For example on McBSP3:
	 * 16bit samples: size is 128 * 2 = 256 bytes
	 * 32bit samples: size is 128 * 4 = 512 bytes
	 * It is simpler to place constraint for buffer and period based on
	 * channels.
	 * McBSP3 as example again (16 or 32 bit samples):
	 * 1 channel (mono): size is 128 frames (128 words)
	 * 2 channels (stereo): size is 128 / 2 = 64 frames (2 * 64 words)
	 * 4 channels: size is 128 / 4 = 32 frames (4 * 32 words)
	 */
	if (mcbsp->pdata->buffer_size) {
		/*
		* Rule for the buffer size. We should not allow
		* smaller buffer than the FIFO size to avoid underruns.
		* This applies only for the playback stream.
		*/
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			snd_pcm_hw_rule_add(substream->runtime, 0,
					    SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					    omap_mcbsp_hwrule_min_buffersize,
					    mcbsp,
					    SNDRV_PCM_HW_PARAM_CHANNELS, -1);

		/* Make sure, that the period size is always even */
		snd_pcm_hw_constraint_step(substream->runtime, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 2);
	}

	return err;
}