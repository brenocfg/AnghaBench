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
struct snd_pcm_hw_params {int dummy; } ;
struct ep93xx_i2s_info {int /*<<< orphan*/  sclk; int /*<<< orphan*/  lrclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP93XX_I2S_RXWRDLEN ; 
 int /*<<< orphan*/  EP93XX_I2S_TXWRDLEN ; 
 unsigned int EP93XX_I2S_WRDLEN_16 ; 
 unsigned int EP93XX_I2S_WRDLEN_24 ; 
 unsigned int EP93XX_I2S_WRDLEN_32 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ep93xx_i2s_enable (struct ep93xx_i2s_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_i2s_write_reg (struct ep93xx_i2s_info*,int /*<<< orphan*/ ,unsigned int) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct ep93xx_i2s_info* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int ep93xx_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct ep93xx_i2s_info *info = snd_soc_dai_get_drvdata(dai);
	unsigned word_len, div, sdiv, lrdiv;
	int err;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		word_len = EP93XX_I2S_WRDLEN_16;
		break;

	case SNDRV_PCM_FORMAT_S24_LE:
		word_len = EP93XX_I2S_WRDLEN_24;
		break;

	case SNDRV_PCM_FORMAT_S32_LE:
		word_len = EP93XX_I2S_WRDLEN_32;
		break;

	default:
		return -EINVAL;
	}

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		ep93xx_i2s_write_reg(info, EP93XX_I2S_TXWRDLEN, word_len);
	else
		ep93xx_i2s_write_reg(info, EP93XX_I2S_RXWRDLEN, word_len);

	/*
	 * EP93xx I2S module can be setup so SCLK / LRCLK value can be
	 * 32, 64, 128. MCLK / SCLK value can be 2 and 4.
	 * We set LRCLK equal to `rate' and minimum SCLK / LRCLK 
	 * value is 64, because our sample size is 32 bit * 2 channels.
	 * I2S standard permits us to transmit more bits than
	 * the codec uses.
	 */
	div = clk_get_rate(info->mclk) / params_rate(params);
	sdiv = 4;
	if (div > (256 + 512) / 2) {
		lrdiv = 128;
	} else {
		lrdiv = 64;
		if (div < (128 + 256) / 2)
			sdiv = 2;
	}

	err = clk_set_rate(info->sclk, clk_get_rate(info->mclk) / sdiv);
	if (err)
		return err;

	err = clk_set_rate(info->lrclk, clk_get_rate(info->sclk) / lrdiv);
	if (err)
		return err;

	ep93xx_i2s_enable(info, substream->stream);
	return 0;
}