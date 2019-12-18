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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  mute; } ;
struct spdif_out_dev {scalar_t__ io_base; TYPE_1__ saved_params; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int SPDIF_OPMODE_AUD_DATA ; 
 int SPDIF_OPMODE_MASK ; 
 int SPDIF_OPMODE_MUTE_PCM ; 
 int SPDIF_OPMODE_OFF ; 
 scalar_t__ SPDIF_OUT_CTRL ; 
 int SPDIF_STATE_NORMAL ; 
 int readl (scalar_t__) ; 
 struct spdif_out_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int spdif_out_trigger(struct snd_pcm_substream *substream, int cmd,
		struct snd_soc_dai *dai)
{
	struct spdif_out_dev *host = snd_soc_dai_get_drvdata(dai);
	u32 ctrl;
	int ret = 0;

	if (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		return -EINVAL;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			ctrl = readl(host->io_base + SPDIF_OUT_CTRL);
			ctrl &= ~SPDIF_OPMODE_MASK;
			if (!host->saved_params.mute)
				ctrl |= SPDIF_OPMODE_AUD_DATA |
					SPDIF_STATE_NORMAL;
			else
				ctrl |= SPDIF_OPMODE_MUTE_PCM;
			writel(ctrl, host->io_base + SPDIF_OUT_CTRL);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl = readl(host->io_base + SPDIF_OUT_CTRL);
		ctrl &= ~SPDIF_OPMODE_MASK;
		ctrl |= SPDIF_OPMODE_OFF;
		writel(ctrl, host->io_base + SPDIF_OUT_CTRL);
		break;

	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}