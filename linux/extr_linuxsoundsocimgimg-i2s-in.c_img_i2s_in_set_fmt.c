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
struct img_i2s_in {int active_channels; int max_i2s_chan; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_I2S_IN_CH_CTL ; 
 int IMG_I2S_IN_CH_CTL_BLKP_MASK ; 
 int IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK ; 
 int IMG_I2S_IN_CH_CTL_LRD_MASK ; 
#define  SND_SOC_DAIFMT_CBM_CFM 134 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  img_i2s_in_ch_disable (struct img_i2s_in*,int) ; 
 int /*<<< orphan*/  img_i2s_in_ch_enable (struct img_i2s_in*,int) ; 
 int img_i2s_in_ch_readl (struct img_i2s_in*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_in_ch_writel (struct img_i2s_in*,int,int,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct img_i2s_in* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_i2s_in_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);
	int i, ret;
	u32 chan_control_mask, lrd_set = 0, blkp_set = 0, chan_control_set = 0;
	u32 reg;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		lrd_set |= IMG_I2S_IN_CH_CTL_LRD_MASK;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		break;
	case SND_SOC_DAIFMT_IB_NF:
		lrd_set |= IMG_I2S_IN_CH_CTL_LRD_MASK;
		blkp_set |= IMG_I2S_IN_CH_CTL_BLKP_MASK;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		blkp_set |= IMG_I2S_IN_CH_CTL_BLKP_MASK;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		chan_control_set |= IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	chan_control_mask = IMG_I2S_IN_CH_CTL_CLK_TRANS_MASK;

	ret = pm_runtime_get_sync(i2s->dev);
	if (ret < 0)
		return ret;

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_disable(i2s, i);

	/*
	 * BLKP and LRD must be set during separate register writes
	 */
	for (i = 0; i < i2s->max_i2s_chan; i++) {
		reg = img_i2s_in_ch_readl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~IMG_I2S_IN_CH_CTL_BLKP_MASK) | blkp_set;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~IMG_I2S_IN_CH_CTL_LRD_MASK) | lrd_set;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	}

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_enable(i2s, i);

	pm_runtime_put(i2s->dev);

	return 0;
}