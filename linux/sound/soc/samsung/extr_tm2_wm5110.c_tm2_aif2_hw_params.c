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
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_ASYNCCLK ; 
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL2 ; 
 int /*<<< orphan*/  ARIZONA_FLL_SRC_MCLK1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  MCLK_RATE ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  WM5110_FLL2 ; 
 int /*<<< orphan*/  WM5110_FLL2_REFCLK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_aif2_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = rtd->codec_dai->component;
	unsigned int asyncclk_rate;
	int ret;

	switch (params_rate(params)) {
	case 8000:
	case 12000:
	case 16000:
		/* Highest possible ASYNCCLK frequency: 49.152MHz */
		asyncclk_rate = 49152000U;
		break;
	case 11025:
		/* Highest possible ASYNCCLK frequency: 45.1584 MHz */
		asyncclk_rate = 45158400U;
		break;
	default:
		dev_err(component->dev, "Not supported sample rate: %d\n",
			params_rate(params));
		return -EINVAL;
	}

	ret = snd_soc_component_set_pll(component, WM5110_FLL2_REFCLK,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    asyncclk_rate);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set FLL2 source: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_set_pll(component, WM5110_FLL2,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    asyncclk_rate);
	if (ret < 0) {
		dev_err(component->dev, "Failed to start FLL2: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_ASYNCCLK,
				       ARIZONA_CLK_SRC_FLL2,
				       asyncclk_rate,
				       SND_SOC_CLOCK_IN);
	if (ret < 0) {
		dev_err(component->dev, "Failed to set ASYNCCLK source: %d\n", ret);
		return ret;
	}

	return 0;
}