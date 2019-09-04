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
struct img_i2s_out {int active_channels; int max_i2s_chan; int force_clk_active; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IMG_I2S_OUT_CHAN_CTL_CLKT_MASK ; 
 int /*<<< orphan*/  IMG_I2S_OUT_CH_CTL ; 
 int /*<<< orphan*/  IMG_I2S_OUT_CTL ; 
 int IMG_I2S_OUT_CTL_BCLK_POL_MASK ; 
 int IMG_I2S_OUT_CTL_CLK_EN_MASK ; 
 int IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK ; 
 int IMG_I2S_OUT_CTL_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_CBM_CFM 135 
#define  SND_SOC_DAIFMT_CBS_CFS 134 
 unsigned int SND_SOC_DAIFMT_CLOCK_MASK ; 
 unsigned int SND_SOC_DAIFMT_CONT ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 133 
#define  SND_SOC_DAIFMT_IB_IF 132 
#define  SND_SOC_DAIFMT_IB_NF 131 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 130 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 129 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int /*<<< orphan*/  img_i2s_out_ch_disable (struct img_i2s_out*,int) ; 
 int /*<<< orphan*/  img_i2s_out_ch_enable (struct img_i2s_out*,int) ; 
 int img_i2s_out_ch_readl (struct img_i2s_out*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_out_ch_writel (struct img_i2s_out*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_out_disable (struct img_i2s_out*) ; 
 int /*<<< orphan*/  img_i2s_out_enable (struct img_i2s_out*) ; 
 int img_i2s_out_readl (struct img_i2s_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_out_writel (struct img_i2s_out*,int,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct img_i2s_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_i2s_out_set_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct img_i2s_out *i2s = snd_soc_dai_get_drvdata(dai);
	int i, ret;
	bool force_clk_active;
	u32 chan_control_mask, control_mask, chan_control_set = 0;
	u32 reg, control_set = 0;

	force_clk_active = ((fmt & SND_SOC_DAIFMT_CLOCK_MASK) ==
			SND_SOC_DAIFMT_CONT);

	if (force_clk_active)
		control_set |= IMG_I2S_OUT_CTL_CLK_EN_MASK;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		control_set |= IMG_I2S_OUT_CTL_MASTER_MASK;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		control_set |= IMG_I2S_OUT_CTL_BCLK_POL_MASK;
		break;
	case SND_SOC_DAIFMT_NB_IF:
		control_set |= IMG_I2S_OUT_CTL_BCLK_POL_MASK;
		control_set |= IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		break;
	case SND_SOC_DAIFMT_IB_IF:
		control_set |= IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		chan_control_set |= IMG_I2S_OUT_CHAN_CTL_CLKT_MASK;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		break;
	default:
		return -EINVAL;
	}

	control_mask = IMG_I2S_OUT_CTL_CLK_EN_MASK |
		       IMG_I2S_OUT_CTL_MASTER_MASK |
		       IMG_I2S_OUT_CTL_BCLK_POL_MASK |
		       IMG_I2S_OUT_CTL_FRM_CLK_POL_MASK;

	chan_control_mask = IMG_I2S_OUT_CHAN_CTL_CLKT_MASK;

	ret = pm_runtime_get_sync(i2s->dev);
	if (ret < 0)
		return ret;

	img_i2s_out_disable(i2s);

	reg = img_i2s_out_readl(i2s, IMG_I2S_OUT_CTL);
	reg = (reg & ~control_mask) | control_set;
	img_i2s_out_writel(i2s, reg, IMG_I2S_OUT_CTL);

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_out_ch_disable(i2s, i);

	for (i = 0; i < i2s->max_i2s_chan; i++) {
		reg = img_i2s_out_ch_readl(i2s, i, IMG_I2S_OUT_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_out_ch_writel(i2s, i, reg, IMG_I2S_OUT_CH_CTL);
	}

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_out_ch_enable(i2s, i);

	img_i2s_out_enable(i2s);
	pm_runtime_put(i2s->dev);

	i2s->force_clk_active = force_clk_active;

	return 0;
}