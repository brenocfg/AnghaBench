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
struct snd_soc_dai {TYPE_1__* component; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BYT_RT5640_MCLK_25MHZ ; 
 int BYT_RT5640_MCLK_EN ; 
 int BYT_RT5640_SSP0_AIF1 ; 
 int BYT_RT5640_SSP0_AIF2 ; 
 int /*<<< orphan*/  RT5640_PLL1_S_BCLK1 ; 
 int /*<<< orphan*/  RT5640_PLL1_S_MCLK ; 
 int /*<<< orphan*/  RT5640_SCLK_S_PLL1 ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int byt_rt5640_quirk ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_rt5640_prepare_and_enable_pll1(struct snd_soc_dai *codec_dai,
					      int rate)
{
	int ret;

	/* Configure the PLL before selecting it */
	if (!(byt_rt5640_quirk & BYT_RT5640_MCLK_EN)) {
		/* use bitclock as PLL input */
		if ((byt_rt5640_quirk & BYT_RT5640_SSP0_AIF1) ||
		    (byt_rt5640_quirk & BYT_RT5640_SSP0_AIF2)) {
			/* 2x16 bit slots on SSP0 */
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_BCLK1,
						  rate * 32, rate * 512);
		} else {
			/* 2x15 bit slots on SSP2 */
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_BCLK1,
						  rate * 50, rate * 512);
		}
	} else {
		if (byt_rt5640_quirk & BYT_RT5640_MCLK_25MHZ) {
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_MCLK,
						  25000000, rate * 512);
		} else {
			ret = snd_soc_dai_set_pll(codec_dai, 0,
						  RT5640_PLL1_S_MCLK,
						  19200000, rate * 512);
		}
	}

	if (ret < 0) {
		dev_err(codec_dai->component->dev, "can't set pll: %d\n", ret);
		return ret;
	}

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5640_SCLK_S_PLL1,
				     rate * 512, SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(codec_dai->component->dev, "can't set clock %d\n", ret);
		return ret;
	}

	return 0;
}