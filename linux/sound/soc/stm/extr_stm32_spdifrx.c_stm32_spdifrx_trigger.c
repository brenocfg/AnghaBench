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
struct stm32_spdifrx_data {int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  SPDIFRX_CR_RXDMAEN ; 
 int /*<<< orphan*/  SPDIFRX_IMR_OVRIE ; 
 int /*<<< orphan*/  STM32_SPDIFRX_CR ; 
 int /*<<< orphan*/  STM32_SPDIFRX_IMR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_spdifrx_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int stm32_spdifrx_start_sync (struct stm32_spdifrx_data*) ; 
 int /*<<< orphan*/  stm32_spdifrx_stop (struct stm32_spdifrx_data*) ; 

__attribute__((used)) static int stm32_spdifrx_trigger(struct snd_pcm_substream *substream, int cmd,
				 struct snd_soc_dai *cpu_dai)
{
	struct stm32_spdifrx_data *spdifrx = snd_soc_dai_get_drvdata(cpu_dai);
	int ret = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_IMR,
				   SPDIFRX_IMR_OVRIE, SPDIFRX_IMR_OVRIE);

		regmap_update_bits(spdifrx->regmap, STM32_SPDIFRX_CR,
				   SPDIFRX_CR_RXDMAEN, SPDIFRX_CR_RXDMAEN);

		ret = stm32_spdifrx_start_sync(spdifrx);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_STOP:
		stm32_spdifrx_stop(spdifrx);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}