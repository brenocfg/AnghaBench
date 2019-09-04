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
typedef  unsigned int u32 ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct img_i2s_in {int max_i2s_chan; int active_channels; } ;
typedef  int snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_I2S_IN_CH_CTL ; 
 unsigned int IMG_I2S_IN_CH_CTL_16PACK_MASK ; 
 unsigned int IMG_I2S_IN_CH_CTL_FEN_MASK ; 
 unsigned int IMG_I2S_IN_CH_CTL_FMODE_MASK ; 
 unsigned int IMG_I2S_IN_CH_CTL_FW_MASK ; 
 unsigned int IMG_I2S_IN_CH_CTL_PACKH_MASK ; 
 unsigned int IMG_I2S_IN_CH_CTL_SW_MASK ; 
 int /*<<< orphan*/  IMG_I2S_IN_CTL ; 
 unsigned int IMG_I2S_IN_CTL_16PACK_MASK ; 
 unsigned int IMG_I2S_IN_CTL_ACTIVE_CHAN_MASK ; 
 unsigned int IMG_I2S_IN_CTL_ACTIVE_CH_SHIFT ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  img_i2s_in_ch_disable (struct img_i2s_in*,int) ; 
 int /*<<< orphan*/  img_i2s_in_ch_enable (struct img_i2s_in*,int) ; 
 unsigned int img_i2s_in_ch_readl (struct img_i2s_in*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_in_ch_writel (struct img_i2s_in*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int img_i2s_in_check_rate (struct img_i2s_in*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  img_i2s_in_flush (struct img_i2s_in*) ; 
 unsigned int img_i2s_in_readl (struct img_i2s_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_in_writel (struct img_i2s_in*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct img_i2s_in* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_i2s_in_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct img_i2s_in *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int rate, channels, i2s_channels, frame_size;
	unsigned int bclk_filter_enable, bclk_filter_value;
	int i, ret = 0;
	u32 reg, control_mask, chan_control_mask;
	u32 control_set = 0, chan_control_set = 0;
	snd_pcm_format_t format;

	rate = params_rate(params);
	format = params_format(params);
	channels = params_channels(params);
	i2s_channels = channels / 2;

	switch (format) {
	case SNDRV_PCM_FORMAT_S32_LE:
		frame_size = 64;
		chan_control_set |= IMG_I2S_IN_CH_CTL_SW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_FW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_PACKH_MASK;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		frame_size = 64;
		chan_control_set |= IMG_I2S_IN_CH_CTL_SW_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_FW_MASK;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		frame_size = 32;
		control_set |= IMG_I2S_IN_CTL_16PACK_MASK;
		chan_control_set |= IMG_I2S_IN_CH_CTL_16PACK_MASK;
		break;
	default:
		return -EINVAL;
	}

	if ((channels < 2) ||
	    (channels > (i2s->max_i2s_chan * 2)) ||
	    (channels % 2))
		return -EINVAL;

	control_set |= ((i2s_channels - 1) << IMG_I2S_IN_CTL_ACTIVE_CH_SHIFT);

	ret = img_i2s_in_check_rate(i2s, rate, frame_size,
			&bclk_filter_enable, &bclk_filter_value);
	if (ret < 0)
		return ret;

	if (bclk_filter_enable)
		chan_control_set |= IMG_I2S_IN_CH_CTL_FEN_MASK;

	if (bclk_filter_value)
		chan_control_set |= IMG_I2S_IN_CH_CTL_FMODE_MASK;

	control_mask = IMG_I2S_IN_CTL_16PACK_MASK |
		       IMG_I2S_IN_CTL_ACTIVE_CHAN_MASK;

	chan_control_mask = IMG_I2S_IN_CH_CTL_16PACK_MASK |
			    IMG_I2S_IN_CH_CTL_FEN_MASK |
			    IMG_I2S_IN_CH_CTL_FMODE_MASK |
			    IMG_I2S_IN_CH_CTL_SW_MASK |
			    IMG_I2S_IN_CH_CTL_FW_MASK |
			    IMG_I2S_IN_CH_CTL_PACKH_MASK;

	reg = img_i2s_in_readl(i2s, IMG_I2S_IN_CTL);
	reg = (reg & ~control_mask) | control_set;
	img_i2s_in_writel(i2s, reg, IMG_I2S_IN_CTL);

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_disable(i2s, i);

	for (i = 0; i < i2s->max_i2s_chan; i++) {
		reg = img_i2s_in_ch_readl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg = (reg & ~chan_control_mask) | chan_control_set;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	}

	i2s->active_channels = i2s_channels;

	img_i2s_in_flush(i2s);

	for (i = 0; i < i2s->active_channels; i++)
		img_i2s_in_ch_enable(i2s, i);

	return 0;
}