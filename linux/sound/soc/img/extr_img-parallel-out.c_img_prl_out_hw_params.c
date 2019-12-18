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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct img_prl_out {int /*<<< orphan*/  clk_ref; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_PRL_OUT_CTL ; 
 int IMG_PRL_OUT_CTL_PACKH_MASK ; 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int img_prl_out_readl (struct img_prl_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_prl_out_writel (struct img_prl_out*,int,int /*<<< orphan*/ ) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct img_prl_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_prl_out_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct img_prl_out *prl = snd_soc_dai_get_drvdata(dai);
	unsigned int rate, channels;
	u32 reg, control_set = 0;

	rate = params_rate(params);
	channels = params_channels(params);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S32_LE:
		control_set |= IMG_PRL_OUT_CTL_PACKH_MASK;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		break;
	default:
		return -EINVAL;
	}

	if (channels != 2)
		return -EINVAL;

	clk_set_rate(prl->clk_ref, rate * 256);

	reg = img_prl_out_readl(prl, IMG_PRL_OUT_CTL);
	reg = (reg & ~IMG_PRL_OUT_CTL_PACKH_MASK) | control_set;
	img_prl_out_writel(prl, reg, IMG_PRL_OUT_CTL);

	return 0;
}