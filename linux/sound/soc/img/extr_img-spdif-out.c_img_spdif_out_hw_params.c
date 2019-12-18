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
struct snd_pcm_hw_params {int dummy; } ;
struct img_spdif_out {int /*<<< orphan*/  clk_ref; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ snd_pcm_format_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IMG_SPDIF_OUT_CTL ; 
 int /*<<< orphan*/  IMG_SPDIF_OUT_CTL_CLK_MASK ; 
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 long abs (long) ; 
 long clk_get_rate (int /*<<< orphan*/ ) ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,long,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  img_spdif_out_readl (struct img_spdif_out*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_spdif_out_writel (struct img_spdif_out*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_format (struct snd_pcm_hw_params*) ; 
 long params_rate (struct snd_pcm_hw_params*) ; 
 struct img_spdif_out* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int img_spdif_out_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct img_spdif_out *spdif = snd_soc_dai_get_drvdata(dai);
	unsigned int channels;
	long pre_div_a, pre_div_b, diff_a, diff_b, rate, clk_rate;
	u32 reg;
	snd_pcm_format_t format;

	rate = params_rate(params);
	format = params_format(params);
	channels = params_channels(params);

	dev_dbg(spdif->dev, "hw_params rate %ld channels %u format %u\n",
			rate, channels, format);

	if (format != SNDRV_PCM_FORMAT_S32_LE)
		return -EINVAL;

	if (channels != 2)
		return -EINVAL;

	pre_div_a = clk_round_rate(spdif->clk_ref, rate * 256);
	if (pre_div_a < 0)
		return pre_div_a;
	pre_div_b = clk_round_rate(spdif->clk_ref, rate * 384);
	if (pre_div_b < 0)
		return pre_div_b;

	diff_a = abs((pre_div_a / 256) - rate);
	diff_b = abs((pre_div_b / 384) - rate);

	/* If diffs are equal, use lower clock rate */
	if (diff_a > diff_b)
		clk_set_rate(spdif->clk_ref, pre_div_b);
	else
		clk_set_rate(spdif->clk_ref, pre_div_a);

	/*
	 * Another driver (eg machine driver) may have rejected the above
	 * change. Get the current rate and set the register bit according to
	 * the new min diff
	 */
	clk_rate = clk_get_rate(spdif->clk_ref);

	diff_a = abs((clk_rate / 256) - rate);
	diff_b = abs((clk_rate / 384) - rate);

	reg = img_spdif_out_readl(spdif, IMG_SPDIF_OUT_CTL);
	if (diff_a <= diff_b)
		reg &= ~IMG_SPDIF_OUT_CTL_CLK_MASK;
	else
		reg |= IMG_SPDIF_OUT_CTL_CLK_MASK;
	img_spdif_out_writel(spdif, reg, IMG_SPDIF_OUT_CTL);

	return 0;
}