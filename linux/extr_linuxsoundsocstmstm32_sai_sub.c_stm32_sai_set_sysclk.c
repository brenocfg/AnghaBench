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
struct stm32_sai_sub_data {unsigned int mclk_rate; int /*<<< orphan*/  regmap; scalar_t__ master; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SAI_XCR1_NODIV ; 
 int SND_SOC_CLOCK_OUT ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_set_sysclk(struct snd_soc_dai *cpu_dai,
				int clk_id, unsigned int freq, int dir)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int ret;

	if ((dir == SND_SOC_CLOCK_OUT) && sai->master) {
		ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
					 SAI_XCR1_NODIV,
					 (unsigned int)~SAI_XCR1_NODIV);
		if (ret < 0)
			return ret;

		sai->mclk_rate = freq;
		dev_dbg(cpu_dai->dev, "SAI MCLK frequency is %uHz\n", freq);
	}

	return 0;
}