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
struct stm32_sai_sub_data {int slots; int /*<<< orphan*/  regmap; scalar_t__ spdif_frm_cnt; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SAI_DATASIZE_16 ; 
 int /*<<< orphan*/  SAI_DATASIZE_32 ; 
 int /*<<< orphan*/  SAI_DATASIZE_8 ; 
 int SAI_XCR1_DS_MASK ; 
 int SAI_XCR1_DS_SET (int /*<<< orphan*/ ) ; 
 int SAI_XCR1_MONO ; 
 int SAI_XCR2_FFLUSH ; 
 int SAI_XCR2_FTH_MASK ; 
 int SAI_XCR2_FTH_SET (int /*<<< orphan*/ ) ; 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 int /*<<< orphan*/  STM_SAI_CR1_REGX ; 
 int /*<<< orphan*/  STM_SAI_CR2_REGX ; 
 int /*<<< orphan*/  STM_SAI_FIFO_TH_HALF ; 
 scalar_t__ STM_SAI_PROTOCOL_IS_SPDIF (struct stm32_sai_sub_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct stm32_sai_sub_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int stm32_sai_set_config(struct snd_soc_dai *cpu_dai,
				struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct stm32_sai_sub_data *sai = snd_soc_dai_get_drvdata(cpu_dai);
	int cr1, cr1_mask, ret;

	/*
	 * DMA bursts increment is set to 4 words.
	 * SAI fifo threshold is set to half fifo, to keep enough space
	 * for DMA incoming bursts.
	 */
	regmap_write_bits(sai->regmap, STM_SAI_CR2_REGX,
			  SAI_XCR2_FFLUSH | SAI_XCR2_FTH_MASK,
			  SAI_XCR2_FFLUSH |
			  SAI_XCR2_FTH_SET(STM_SAI_FIFO_TH_HALF));

	/* DS bits in CR1 not set for SPDIF (size forced to 24 bits).*/
	if (STM_SAI_PROTOCOL_IS_SPDIF(sai)) {
		sai->spdif_frm_cnt = 0;
		return 0;
	}

	/* Mode, data format and channel config */
	cr1_mask = SAI_XCR1_DS_MASK;
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S8:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_8);
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_16);
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		cr1 = SAI_XCR1_DS_SET(SAI_DATASIZE_32);
		break;
	default:
		dev_err(cpu_dai->dev, "Data format not supported");
		return -EINVAL;
	}

	cr1_mask |= SAI_XCR1_MONO;
	if ((sai->slots == 2) && (params_channels(params) == 1))
		cr1 |= SAI_XCR1_MONO;

	ret = regmap_update_bits(sai->regmap, STM_SAI_CR1_REGX, cr1_mask, cr1);
	if (ret < 0) {
		dev_err(cpu_dai->dev, "Failed to update CR1 register\n");
		return ret;
	}

	return 0;
}