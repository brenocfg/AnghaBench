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
struct snd_soc_pcm_runtime {struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX9485_MCLK_FREQ_112896 ; 
 int /*<<< orphan*/  MAX9485_MCLK_FREQ_122880 ; 
 int /*<<< orphan*/  MAX9485_MCLK_FREQ_225792 ; 
 int /*<<< orphan*/  MAX9485_MCLK_FREQ_245760 ; 
 int /*<<< orphan*/  PXA_SSP_CLK_EXT ; 
 int /*<<< orphan*/  PXA_SSP_DIV_SCR ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  set_max9485_clk (int /*<<< orphan*/ ) ; 
 int snd_soc_dai_set_clkdiv (struct snd_soc_dai*,int /*<<< orphan*/ ,int) ; 
 int snd_soc_dai_set_pll (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_soc_dai_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int raumfeld_ak4104_hw_params(struct snd_pcm_substream *substream,
				     struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int ret = 0, clk = 0;

	switch (params_rate(params)) {
	case 44100:
		set_max9485_clk(MAX9485_MCLK_FREQ_112896);
		clk = 11289600;
		break;
	case 48000:
		set_max9485_clk(MAX9485_MCLK_FREQ_122880);
		clk = 12288000;
		break;
	case 88200:
		set_max9485_clk(MAX9485_MCLK_FREQ_225792);
		clk = 22579200;
		break;
	case 96000:
		set_max9485_clk(MAX9485_MCLK_FREQ_245760);
		clk = 24576000;
		break;
	default:
		return -EINVAL;
	}

	/* setup the CPU DAI */
	ret = snd_soc_dai_set_pll(cpu_dai, 0, 0, 0, clk);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_clkdiv(cpu_dai, PXA_SSP_DIV_SCR, 4);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA_SSP_CLK_EXT, clk, 1);
	if (ret < 0)
		return ret;

	return 0;
}