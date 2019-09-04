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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  s3c24xx_snd_is_clkmaster () ; 
 int s3c24xx_snd_lrsync () ; 
 int /*<<< orphan*/  s3c24xx_snd_rxctrl (int) ; 
 int /*<<< orphan*/  s3c24xx_snd_txctrl (int) ; 

__attribute__((used)) static int s3c24xx_i2s_trigger(struct snd_pcm_substream *substream, int cmd,
			       struct snd_soc_dai *dai)
{
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (!s3c24xx_snd_is_clkmaster()) {
			ret = s3c24xx_snd_lrsync();
			if (ret)
				goto exit_err;
		}

		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c24xx_snd_rxctrl(1);
		else
			s3c24xx_snd_txctrl(1);

		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			s3c24xx_snd_rxctrl(0);
		else
			s3c24xx_snd_txctrl(0);
		break;
	default:
		ret = -EINVAL;
		break;
	}

exit_err:
	return ret;
}