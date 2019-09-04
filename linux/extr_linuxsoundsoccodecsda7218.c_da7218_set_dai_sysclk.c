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
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct da7218_priv {unsigned int mclk_rate; scalar_t__ mclk; } ;

/* Variables and functions */
#define  DA7218_CLKSRC_MCLK 129 
#define  DA7218_CLKSRC_MCLK_SQR 128 
 int /*<<< orphan*/  DA7218_PLL_CTRL ; 
 int /*<<< orphan*/  DA7218_PLL_MCLK_SQR_EN_MASK ; 
 int EINVAL ; 
 unsigned int clk_round_rate (scalar_t__,unsigned int) ; 
 int clk_set_rate (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7218_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	int ret;

	if (da7218->mclk_rate == freq)
		return 0;

	if ((freq < 2000000) || (freq > 54000000)) {
		dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
			freq);
		return -EINVAL;
	}

	switch (clk_id) {
	case DA7218_CLKSRC_MCLK_SQR:
		snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
				    DA7218_PLL_MCLK_SQR_EN_MASK,
				    DA7218_PLL_MCLK_SQR_EN_MASK);
		break;
	case DA7218_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, DA7218_PLL_CTRL,
				    DA7218_PLL_MCLK_SQR_EN_MASK, 0);
		break;
	default:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		return -EINVAL;
	}

	if (da7218->mclk) {
		freq = clk_round_rate(da7218->mclk, freq);
		ret = clk_set_rate(da7218->mclk, freq);
		if (ret) {
			dev_err(codec_dai->dev, "Failed to set clock rate %d\n",
				freq);
			return ret;
		}
	}

	da7218->mclk_rate = freq;

	return 0;
}