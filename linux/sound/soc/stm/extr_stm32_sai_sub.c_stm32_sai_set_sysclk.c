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
struct stm32_sai_sub_data {int mclk_rate; scalar_t__ sai_mclk; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SAI_XCR1_NODIV ; 
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  clk_rate_exclusive_put (scalar_t__) ; 
 int clk_set_rate_exclusive (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stm32_sai_set_parent_clock (struct stm32_sai_sub_data*,unsigned int) ; 

__attribute__((used)) static int stm32_sai_set_sysclk(struct snd_soc_dai *cpu_dai,
				int clk_id, unsigned int freq, int dir)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int ret;

	if (dir == SND_SOC_CLOCK_OUT && sai->sai_mclk) {
		ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
					 SAI_XCR1_NODIV,
					 freq ? 0 : SAI_XCR1_NODIV);
		if (ret < 0)
			return ret;

		/* Assume shutdown if requested frequency is 0Hz */
		if (!freq) {
			/* Release mclk rate only if rate was actually set */
			if (sai->mclk_rate) {
				clk_rate_exclusive_put(sai->sai_mclk);
				sai->mclk_rate = 0;
			}
			return 0;
		}

		/* If master clock is used, set parent clock now */
		ret = stm32_sai_set_parent_clock(sai, freq);
		if (ret)
			return ret;

		ret = clk_set_rate_exclusive(sai->sai_mclk, freq);
		if (ret) {
			dev_err(cpu_dai->dev,
				ret == -EBUSY ?
				"Active streams have incompatible rates" :
				"Could not set mclk rate\n");
			return ret;
		}

		dev_dbg(cpu_dai->dev, "SAI MCLK frequency is %uHz\n", freq);
		sai->mclk_rate = freq;
	}

	return 0;
}