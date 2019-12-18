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
struct snd_pcm_substream {int stream; } ;
struct au1xpsc_audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97PCR_CLRFIFO (int) ; 
 int /*<<< orphan*/  AC97PCR_START (int) ; 
 int /*<<< orphan*/  AC97PCR_STOP (int) ; 
 int AC97STAT_BUSY (int) ; 
 int /*<<< orphan*/  AC97_PCR (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  AC97_STAT (struct au1xpsc_audio_data*) ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_ac97_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct au1xpsc_audio_data *pscdata = snd_soc_dai_get_drvdata(dai);
	int ret, stype = substream->stream;

	ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		__raw_writel(AC97PCR_CLRFIFO(stype), AC97_PCR(pscdata));
		wmb(); /* drain writebuffer */
		__raw_writel(AC97PCR_START(stype), AC97_PCR(pscdata));
		wmb(); /* drain writebuffer */
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		__raw_writel(AC97PCR_STOP(stype), AC97_PCR(pscdata));
		wmb(); /* drain writebuffer */

		while (__raw_readl(AC97_STAT(pscdata)) & AC97STAT_BUSY(stype))
			asm volatile ("nop");

		__raw_writel(AC97PCR_CLRFIFO(stype), AC97_PCR(pscdata));
		wmb(); /* drain writebuffer */

		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}