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
typedef  int uint32_t ;
struct snd_soc_dai {int /*<<< orphan*/  id; } ;
struct snd_pcm_substream {int dummy; } ;
struct kirkwood_dma_data {int ctl_rec; scalar_t__ io; } ;

/* Variables and functions */
 int EINVAL ; 
 int KIRKWOOD_INT_CAUSE_REC_BYTES ; 
 scalar_t__ KIRKWOOD_INT_MASK ; 
 scalar_t__ KIRKWOOD_RECCTL ; 
 int KIRKWOOD_RECCTL_ENABLE_MASK ; 
 int KIRKWOOD_RECCTL_I2S_EN ; 
 int KIRKWOOD_RECCTL_MUTE ; 
 int KIRKWOOD_RECCTL_PAUSE ; 
 int KIRKWOOD_RECCTL_SPDIF_EN ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int readl (scalar_t__) ; 
 struct kirkwood_dma_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int kirkwood_i2s_rec_trigger(struct snd_pcm_substream *substream,
				int cmd, struct snd_soc_dai *dai)
{
	struct kirkwood_dma_data *priv = snd_soc_dai_get_drvdata(dai);
	uint32_t ctl, value;

	value = readl(priv->io + KIRKWOOD_RECCTL);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* configure */
		ctl = priv->ctl_rec;
		if (dai->id == 0)
			ctl &= ~KIRKWOOD_RECCTL_SPDIF_EN;	/* i2s */
		else
			ctl &= ~KIRKWOOD_RECCTL_I2S_EN;		/* spdif */

		value = ctl & ~KIRKWOOD_RECCTL_ENABLE_MASK;
		writel(value, priv->io + KIRKWOOD_RECCTL);

		/* enable interrupts */
		value = readl(priv->io + KIRKWOOD_INT_MASK);
		value |= KIRKWOOD_INT_CAUSE_REC_BYTES;
		writel(value, priv->io + KIRKWOOD_INT_MASK);

		/* enable record */
		writel(ctl, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
		/* stop audio, disable interrupts */
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		writel(value, priv->io + KIRKWOOD_RECCTL);

		value = readl(priv->io + KIRKWOOD_INT_MASK);
		value &= ~KIRKWOOD_INT_CAUSE_REC_BYTES;
		writel(value, priv->io + KIRKWOOD_INT_MASK);

		/* disable all records */
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value &= ~KIRKWOOD_RECCTL_ENABLE_MASK;
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value |= KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE;
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		value = readl(priv->io + KIRKWOOD_RECCTL);
		value &= ~(KIRKWOOD_RECCTL_PAUSE | KIRKWOOD_RECCTL_MUTE);
		writel(value, priv->io + KIRKWOOD_RECCTL);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}