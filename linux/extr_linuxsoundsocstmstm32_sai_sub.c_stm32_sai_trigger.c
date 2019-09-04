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
struct stm32_sai_sub_data {int /*<<< orphan*/  spdif_frm_cnt; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SAI_XCR1_DMAEN ; 
 unsigned int SAI_XCR1_SAIEN ; 
 unsigned int SAI_XIMR_MASK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  STM_SAI_IMR_REGX ; 
 int /*<<< orphan*/  STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_trigger(struct snd_pcm_substream *substream, int cmd,
			     struct snd_soc_dai *cpu_dai)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dev_dbg(cpu_dai->dev, "Enable DMA and SAI\n");

		regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
				   SAI_XCR1_DMAEN, SAI_XCR1_DMAEN);

		/* Enable SAI */
		ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
					 SAI_XCR1_SAIEN, SAI_XCR1_SAIEN);
		if (ret < 0)
			dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(cpu_dai->dev, "Disable DMA and SAI\n");

		regmap_update_bits(sai->regmap, STM_SAI_IMR_REGX,
				   SAI_XIMR_MASK, 0);

		regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
				   SAI_XCR1_SAIEN,
				   (unsigned int)~SAI_XCR1_SAIEN);

		ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX,
					 SAI_XCR1_DMAEN,
					 (unsigned int)~SAI_XCR1_DMAEN);
		if (ret < 0)
			dev_err(cpu_dai->dev, "Failed to update CR1 register\n");

		if (STM_SAI_PROTOCOL_IS_SPDIF(sai))
			sai->spdif_frm_cnt = 0;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}