#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sun4i_i2s {unsigned int mclk_freq; int /*<<< orphan*/  field_clkdiv_mclk_en; int /*<<< orphan*/  regmap; TYPE_1__* variant; int /*<<< orphan*/  mod_clk; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned int (* get_bclk_parent_rate ) (struct sun4i_i2s*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int SUN4I_I2S_CLK_DIV_BCLK (int) ; 
 int SUN4I_I2S_CLK_DIV_MCLK (int) ; 
 int /*<<< orphan*/  SUN4I_I2S_CLK_DIV_REG ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sun4i_i2s* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 unsigned int stub1 (struct sun4i_i2s*) ; 
 int sun4i_i2s_get_bclk_div (struct sun4i_i2s*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int sun4i_i2s_get_mclk_div (struct sun4i_i2s*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sun4i_i2s_oversample_is_valid (unsigned int) ; 

__attribute__((used)) static int sun4i_i2s_set_clk_rate(struct snd_soc_dai *dai,
				  unsigned int rate,
				  unsigned int slots,
				  unsigned int slot_width)
{
	struct sun4i_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	unsigned int oversample_rate, clk_rate, bclk_parent_rate;
	int bclk_div, mclk_div;
	int ret;

	switch (rate) {
	case 176400:
	case 88200:
	case 44100:
	case 22050:
	case 11025:
		clk_rate = 22579200;
		break;

	case 192000:
	case 128000:
	case 96000:
	case 64000:
	case 48000:
	case 32000:
	case 24000:
	case 16000:
	case 12000:
	case 8000:
		clk_rate = 24576000;
		break;

	default:
		dev_err(dai->dev, "Unsupported sample rate: %u\n", rate);
		return -EINVAL;
	}

	ret = clk_set_rate(i2s->mod_clk, clk_rate);
	if (ret)
		return ret;

	oversample_rate = i2s->mclk_freq / rate;
	if (!sun4i_i2s_oversample_is_valid(oversample_rate)) {
		dev_err(dai->dev, "Unsupported oversample rate: %d\n",
			oversample_rate);
		return -EINVAL;
	}

	bclk_parent_rate = i2s->variant->get_bclk_parent_rate(i2s);
	bclk_div = sun4i_i2s_get_bclk_div(i2s, bclk_parent_rate,
					  rate, slots, slot_width);
	if (bclk_div < 0) {
		dev_err(dai->dev, "Unsupported BCLK divider: %d\n", bclk_div);
		return -EINVAL;
	}

	mclk_div = sun4i_i2s_get_mclk_div(i2s, clk_rate, i2s->mclk_freq);
	if (mclk_div < 0) {
		dev_err(dai->dev, "Unsupported MCLK divider: %d\n", mclk_div);
		return -EINVAL;
	}

	regmap_write(i2s->regmap, SUN4I_I2S_CLK_DIV_REG,
		     SUN4I_I2S_CLK_DIV_BCLK(bclk_div) |
		     SUN4I_I2S_CLK_DIV_MCLK(mclk_div));

	regmap_field_write(i2s->field_clkdiv_mclk_en, 1);

	return 0;
}