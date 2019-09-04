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
struct stm32_i2s_data {int dummy; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 scalar_t__ STM32_I2S_IS_MASTER (struct stm32_i2s_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct stm32_i2s_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stm32_i2s_configure (struct snd_soc_dai*,struct snd_pcm_hw_params*,struct snd_pcm_substream*) ; 
 int stm32_i2s_configure_clock (struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int stm32_i2s_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *params,
			       struct snd_soc_dai *cpu_dai)
{
	struct stm32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	int ret;

	ret = stm32_i2s_configure(cpu_dai, params, substream);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Configuration returned error %d\n", ret);
		return ret;
	}

	if (STM32_I2S_IS_MASTER(i2s))
		ret = stm32_i2s_configure_clock(cpu_dai, params);

	return ret;
}