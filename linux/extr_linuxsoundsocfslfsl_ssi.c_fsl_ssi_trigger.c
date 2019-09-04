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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct fsl_ssi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  fsl_ssi_config_disable (struct fsl_ssi*,int) ; 
 int /*<<< orphan*/  fsl_ssi_config_enable (struct fsl_ssi*,int) ; 
 int /*<<< orphan*/  fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 int /*<<< orphan*/  fsl_ssi_tx_ac97_saccst_setup (struct fsl_ssi*) ; 
 struct fsl_ssi* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_ssi_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct fsl_ssi *ssi = snd_soc_dai_get_drvdata(rtd->cpu_dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * SACCST might be modified via AC Link by a CODEC if it sends
		 * extra bits in their SLOTREQ requests, which'll accidentally
		 * send valid data to slots other than normal playback slots.
		 *
		 * To be safe, configure SACCST right before TX starts.
		 */
		if (tx && fsl_ssi_is_ac97(ssi))
			fsl_ssi_tx_ac97_saccst_setup(ssi);
		fsl_ssi_config_enable(ssi, tx);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		fsl_ssi_config_disable(ssi, tx);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}