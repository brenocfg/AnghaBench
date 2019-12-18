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
struct stm32_sai_sub_data {int mclk_rate; int fs_length; int /*<<< orphan*/  regmap; int /*<<< orphan*/  pdata; int /*<<< orphan*/  sai_ck; int /*<<< orphan*/  sai_mclk; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SAI_XCR1_OSR ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 scalar_t__ STM_SAI_IS_F4 (int /*<<< orphan*/ ) ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stm32_sai_get_clk_div (struct stm32_sai_sub_data*,int,int) ; 
 int stm32_sai_set_clk_div (struct stm32_sai_sub_data*,int) ; 
 int stm32_sai_set_parent_clock (struct stm32_sai_sub_data*,unsigned int) ; 

__attribute__((used)) static int stm32_sai_configure_clock(struct snd_soc_dai *cpu_dai,
				     struct snd_pcm_hw_params *params)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int div = 0, cr1 = 0;
	int sai_clk_rate, mclk_ratio, den;
	unsigned int rate = params_rate(params);
	int ret;

	if (!sai->sai_mclk) {
		ret = stm32_sai_set_parent_clock(sai, rate);
		if (ret)
			return ret;
	}
	sai_clk_rate = clk_get_rate(sai->sai_ck);

	if (STM_SAI_IS_F4(sai->pdata)) {
		/* mclk on (NODIV=0)
		 *   mclk_rate = 256 * fs
		 *   MCKDIV = 0 if sai_ck < 3/2 * mclk_rate
		 *   MCKDIV = sai_ck / (2 * mclk_rate) otherwise
		 * mclk off (NODIV=1)
		 *   MCKDIV ignored. sck = sai_ck
		 */
		if (!sai->mclk_rate)
			return 0;

		if (2 * sai_clk_rate >= 3 * sai->mclk_rate) {
			div = stm32_sai_get_clk_div(sai, sai_clk_rate,
						    2 * sai->mclk_rate);
			if (div < 0)
				return div;
		}
	} else {
		/*
		 * TDM mode :
		 *   mclk on
		 *      MCKDIV = sai_ck / (ws x 256)	(NOMCK=0. OSR=0)
		 *      MCKDIV = sai_ck / (ws x 512)	(NOMCK=0. OSR=1)
		 *   mclk off
		 *      MCKDIV = sai_ck / (frl x ws)	(NOMCK=1)
		 * Note: NOMCK/NODIV correspond to same bit.
		 */
		if (STM_SAI_PROTOCOL_IS_SPDIF(sai)) {
			div = stm32_sai_get_clk_div(sai, sai_clk_rate,
						    rate * 128);
			if (div < 0)
				return div;
		} else {
			if (sai->mclk_rate) {
				mclk_ratio = sai->mclk_rate / rate;
				if (mclk_ratio == 512) {
					cr1 = SAI_XCR1_OSR;
				} else if (mclk_ratio != 256) {
					dev_err(cpu_dai->dev,
						"Wrong mclk ratio %d\n",
						mclk_ratio);
					return -EINVAL;
				}

				regmap_update_bits(sai->regmap,
						   STM_SAI_CR1_REGX,
						   SAI_XCR1_OSR, cr1);

				div = stm32_sai_get_clk_div(sai, sai_clk_rate,
							    sai->mclk_rate);
				if (div < 0)
					return div;
			} else {
				/* mclk-fs not set, master clock not active */
				den = sai->fs_length * params_rate(params);
				div = stm32_sai_get_clk_div(sai, sai_clk_rate,
							    den);
				if (div < 0)
					return div;
			}
		}
	}

	return stm32_sai_set_clk_div(sai, div);
}