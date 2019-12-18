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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct img_spdif_out {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_SPDIF_OUT_CTL ; 
 int /*<<< orphan*/  IMG_SPDIF_OUT_CTL_SRT_MASK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  img_spdif_out_readl (struct img_spdif_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_out_reset (struct img_spdif_out*) ; 
 int /*<<< orphan*/  img_spdif_out_writel (struct img_spdif_out*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct img_spdif_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int img_spdif_out_trigger(struct snd_pcm_substream *substream, int cmd,
			struct snd_soc_dai *dai)
{
	struct img_spdif_out *spdif = snd_soc_dai_get_drvdata(dai);
	u32 reg;
	unsigned long flags;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_spdif_out_readl(spdif, IMG_SPDIF_OUT_CTL);
		reg |= IMG_SPDIF_OUT_CTL_SRT_MASK;
		img_spdif_out_writel(spdif, reg, IMG_SPDIF_OUT_CTL);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&spdif->lock, flags);
		img_spdif_out_reset(spdif);
		spin_unlock_irqrestore(&spdif->lock, flags);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}