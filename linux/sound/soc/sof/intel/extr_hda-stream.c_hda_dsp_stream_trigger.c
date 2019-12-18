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
typedef  int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;
struct hdac_stream {int index; int running; } ;
struct hdac_ext_stream {struct hdac_stream hstream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_POLL_INTERVAL_US ; 
 int /*<<< orphan*/  HDA_DSP_STREAM_RUN_TIMEOUT ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  SOF_HDA_ADSP_REG_CL_SD_STS ; 
 int SOF_HDA_CL_DMA_SD_INT_MASK ; 
 int SOF_HDA_INTCTL ; 
 int SOF_HDA_SD_CTL_DMA_START ; 
 int SOF_STREAM_SD_OFFSET (struct hdac_stream*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_sof_dsp_read_poll_timeout (struct snd_sof_dev*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_write (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hda_dsp_stream_trigger(struct snd_sof_dev *sdev,
			   struct hdac_ext_stream *stream, int cmd)
{
	struct hdac_stream *hstream = &stream->hstream;
	int sd_offset = SOF_STREAM_SD_OFFSET(hstream);
	u32 dma_start = SOF_HDA_SD_CTL_DMA_START;
	int ret;
	u32 run;

	/* cmd must be for audio stream */
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_START:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
					1 << hstream->index,
					1 << hstream->index);

		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK);

		ret = snd_sof_dsp_read_poll_timeout(sdev,
					HDA_DSP_HDA_BAR,
					sd_offset, run,
					((run &	dma_start) == dma_start),
					HDA_DSP_REG_POLL_INTERVAL_US,
					HDA_DSP_STREAM_RUN_TIMEOUT);

		if (ret)
			return ret;

		hstream->running = true;
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_STOP:
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR,
					sd_offset,
					SOF_HDA_SD_CTL_DMA_START |
					SOF_HDA_CL_DMA_SD_INT_MASK, 0x0);

		ret = snd_sof_dsp_read_poll_timeout(sdev, HDA_DSP_HDA_BAR,
						sd_offset, run,
						!(run &	dma_start),
						HDA_DSP_REG_POLL_INTERVAL_US,
						HDA_DSP_STREAM_RUN_TIMEOUT);

		if (ret)
			return ret;

		snd_sof_dsp_write(sdev, HDA_DSP_HDA_BAR, sd_offset +
				  SOF_HDA_ADSP_REG_CL_SD_STS,
				  SOF_HDA_CL_DMA_SD_INT_MASK);

		hstream->running = false;
		snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_INTCTL,
					1 << hstream->index, 0x0);
		break;
	default:
		dev_err(sdev->dev, "error: unknown command: %d\n", cmd);
		return -EINVAL;
	}

	return 0;
}