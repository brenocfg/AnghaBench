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
struct da7219_priv {int clk_src; unsigned int mclk_rate; int /*<<< orphan*/  pll_lock; scalar_t__ mclk; } ;

/* Variables and functions */
#define  DA7219_CLKSRC_MCLK 129 
#define  DA7219_CLKSRC_MCLK_SQR 128 
 int /*<<< orphan*/  DA7219_PLL_CTRL ; 
 int /*<<< orphan*/  DA7219_PLL_MCLK_SQR_EN_MASK ; 
 int EINVAL ; 
 unsigned int clk_round_rate (scalar_t__,unsigned int) ; 
 int clk_set_rate (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7219_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);
	int ret = 0;

	if ((da7219->clk_src == clk_id) && (da7219->mclk_rate == freq))
		return 0;

	if ((freq < 2000000) || (freq > 54000000)) {
		dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
			freq);
		return -EINVAL;
	}

	mutex_lock(&da7219->pll_lock);

	switch (clk_id) {
	case DA7219_CLKSRC_MCLK_SQR:
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_MCLK_SQR_EN_MASK,
				    DA7219_PLL_MCLK_SQR_EN_MASK);
		break;
	case DA7219_CLKSRC_MCLK:
		snd_soc_component_update_bits(component, DA7219_PLL_CTRL,
				    DA7219_PLL_MCLK_SQR_EN_MASK, 0);
		break;
	default:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		mutex_unlock(&da7219->pll_lock);
		return -EINVAL;
	}

	da7219->clk_src = clk_id;

	if (da7219->mclk) {
		freq = clk_round_rate(da7219->mclk, freq);
		ret = clk_set_rate(da7219->mclk, freq);
		if (ret) {
			dev_err(codec_dai->dev, "Failed to set clock rate %d\n",
				freq);
			mutex_unlock(&da7219->pll_lock);
			return ret;
		}
	}

	da7219->mclk_rate = freq;

	mutex_unlock(&da7219->pll_lock);

	return 0;
}