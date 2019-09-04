#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_sai_sub_data {int mclk_rate; int fs_length; int /*<<< orphan*/  regmap; TYPE_2__* pdata; int /*<<< orphan*/  sai_ck; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk_x8k; int /*<<< orphan*/  clk_x11k; TYPE_1__* conf; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EINVAL ; 
 int SAI_XCR1_MCKDIV_MASK (int /*<<< orphan*/ ) ; 
 int SAI_XCR1_MCKDIV_MAX (int) ; 
 int SAI_XCR1_MCKDIV_SET (int) ; 
 int /*<<< orphan*/  SAI_XCR1_MCKDIV_WIDTH (int) ; 
 int SAI_XCR1_OSR ; 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 scalar_t__ STM_SAI_IS_F4 (TYPE_2__*) ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_configure_clock(struct snd_soc_dai *cpu_dai,
				     struct snd_pcm_hw_params *params)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int cr1, mask, div = 0;
	int sai_clk_rate, mclk_ratio, den, ret;
	int version = sai->pdata->conf->version;
	unsigned int rate = params_rate(params);

	if (!sai->mclk_rate) {
		dev_err(cpu_dai->dev, "Mclk rate is null\n");
		return -EINVAL;
	}

	if (!(rate % 11025))
		clk_set_parent(sai->sai_ck, sai->pdata->clk_x11k);
	else
		clk_set_parent(sai->sai_ck, sai->pdata->clk_x8k);
	sai_clk_rate = clk_get_rate(sai->sai_ck);

	if (STM_SAI_IS_F4(sai->pdata)) {
		/*
		 * mclk_rate = 256 * fs
		 * MCKDIV = 0 if sai_ck < 3/2 * mclk_rate
		 * MCKDIV = sai_ck / (2 * mclk_rate) otherwise
		 */
		if (2 * sai_clk_rate >= 3 * sai->mclk_rate)
			div = DIV_ROUND_CLOSEST(sai_clk_rate,
						2 * sai->mclk_rate);
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
			div = DIV_ROUND_CLOSEST(sai_clk_rate,
						(params_rate(params) * 128));
		} else {
			if (sai->mclk_rate) {
				mclk_ratio = sai->mclk_rate / rate;
				if (mclk_ratio == 512) {
					mask = SAI_XCR1_OSR;
					cr1 = SAI_XCR1_OSR;
				} else if (mclk_ratio != 256) {
					dev_err(cpu_dai->dev,
						"Wrong mclk ratio %d\n",
						mclk_ratio);
					return -EINVAL;
				}
				div = DIV_ROUND_CLOSEST(sai_clk_rate,
							sai->mclk_rate);
			} else {
				/* mclk-fs not set, master clock not active */
				den = sai->fs_length * params_rate(params);
				div = DIV_ROUND_CLOSEST(sai_clk_rate, den);
			}
		}
	}

	if (div > SAI_XCR1_MCKDIV_MAX(version)) {
		dev_err(cpu_dai->dev, "Divider %d out of range\n", div);
		return -EINVAL;
	}
	dev_dbg(cpu_dai->dev, "SAI clock %d, divider %d\n", sai_clk_rate, div);

	mask = SAI_XCR1_MCKDIV_MASK(SAI_XCR1_MCKDIV_WIDTH(version));
	cr1 = SAI_XCR1_MCKDIV_SET(div);
	ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, mask, cr1);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		return ret;
	}

	return 0;
}