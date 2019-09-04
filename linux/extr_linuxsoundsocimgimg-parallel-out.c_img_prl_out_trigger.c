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
struct img_prl_out {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_PRL_OUT_CTL ; 
 int /*<<< orphan*/  IMG_PRL_OUT_CTL_ME_MASK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  img_prl_out_readl (struct img_prl_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_prl_out_reset (struct img_prl_out*) ; 
 int /*<<< orphan*/  img_prl_out_writel (struct img_prl_out*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct img_prl_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_prl_out_trigger(struct snd_pcm_substream *substream, int cmd,
			struct snd_soc_dai *dai)
{
	struct img_prl_out *prl = snd_soc_dai_get_drvdata(dai);
	u32 reg;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		reg = img_prl_out_readl(prl, IMG_PRL_OUT_CTL);
		reg |= IMG_PRL_OUT_CTL_ME_MASK;
		img_prl_out_writel(prl, reg, IMG_PRL_OUT_CTL);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		img_prl_out_reset(prl);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}