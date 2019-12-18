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
typedef  unsigned long u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct img_spdif_in {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  multi_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_SPDIF_IN_CTL ; 
 unsigned long IMG_SPDIF_IN_CTL_SRD_MASK ; 
 unsigned long IMG_SPDIF_IN_CTL_SRD_SHIFT ; 
 unsigned long IMG_SPDIF_IN_CTL_SRT_MASK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 unsigned long img_spdif_in_readl (struct img_spdif_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_in_writel (struct img_spdif_in*,unsigned long,int /*<<< orphan*/ ) ; 
 struct img_spdif_in* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_in_trigger(struct snd_pcm_substream *substream, int cmd,
	struct snd_soc_dai *dai)
{
	unsigned long flags;
	struct img_spdif_in *spdif = snd_soc_dai_get_drvdata(dai);
	int ret = 0;
	u32 reg;

	spin_lock_irqsave(&spdif->lock, flags);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_spdif_in_readl(spdif, IMG_SPDIF_IN_CTL);
		if (spdif->multi_freq)
			reg &= ~IMG_SPDIF_IN_CTL_SRD_MASK;
		else
			reg |= (1UL << IMG_SPDIF_IN_CTL_SRD_SHIFT);
		reg |= IMG_SPDIF_IN_CTL_SRT_MASK;
		img_spdif_in_writel(spdif, reg, IMG_SPDIF_IN_CTL);
		spdif->active = true;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		reg = img_spdif_in_readl(spdif, IMG_SPDIF_IN_CTL);
		reg &= ~IMG_SPDIF_IN_CTL_SRT_MASK;
		img_spdif_in_writel(spdif, reg, IMG_SPDIF_IN_CTL);
		spdif->active = false;
		break;
	default:
		ret = -EINVAL;
	}

	spin_unlock_irqrestore(&spdif->lock, flags);

	return ret;
}