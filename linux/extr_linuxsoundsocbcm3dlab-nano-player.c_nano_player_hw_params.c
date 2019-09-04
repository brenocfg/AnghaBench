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
struct snd_soc_pcm_runtime {struct snd_soc_card* card; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NANO_CFG ; 
 unsigned int NANO_CFG_CLK22 ; 
 unsigned int NANO_CFG_CLK24 ; 
 unsigned int NANO_CFG_DSD ; 
 unsigned int NANO_CFG_ENA ; 
 unsigned int NANO_CFG_MULT1 ; 
 unsigned int NANO_CFG_MULT16 ; 
 unsigned int NANO_CFG_MULT2 ; 
 unsigned int NANO_CFG_MULT4 ; 
 unsigned int NANO_CFG_MULT8 ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_DSD_U32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_FORMAT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_set (struct snd_mask*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_mask_test (struct snd_mask*,int /*<<< orphan*/ ) ; 
 struct regmap* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 

__attribute__((used)) static int nano_player_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct regmap *regmap = snd_soc_card_get_drvdata(card);
	unsigned int config = NANO_CFG_ENA;
	struct snd_mask *fmt;

	/* configure PCM or DSD */
	fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	if (snd_mask_test(fmt, SNDRV_PCM_FORMAT_DSD_U32_LE)) {
		/* embed DSD in PCM data */
		snd_mask_none(fmt);
		snd_mask_set(fmt, SNDRV_PCM_FORMAT_S32_LE);
		/* enable DSD mode */
		config |= NANO_CFG_DSD;
	}

	/* configure clocks */
	switch (params_rate(params)) {
	case 44100:
		config |= NANO_CFG_MULT1 | NANO_CFG_CLK22;
		break;
	case 88200:
		config |= NANO_CFG_MULT2 | NANO_CFG_CLK22;
		break;
	case 176400:
		config |= NANO_CFG_MULT4 | NANO_CFG_CLK22;
		break;
	case 352800:
		config |= NANO_CFG_MULT8 | NANO_CFG_CLK22;
		break;
	case 705600:
		config |= NANO_CFG_MULT16 | NANO_CFG_CLK22;
		break;
	case 48000:
		config |= NANO_CFG_MULT1 | NANO_CFG_CLK24;
		break;
	case 96000:
		config |= NANO_CFG_MULT2 | NANO_CFG_CLK24;
		break;
	case 192000:
		config |= NANO_CFG_MULT4 | NANO_CFG_CLK24;
		break;
	case 384000:
		config |= NANO_CFG_MULT8 | NANO_CFG_CLK24;
		break;
	case 768000:
		config |= NANO_CFG_MULT16 | NANO_CFG_CLK24;
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(card->dev, "Send CFG register 0x%02X\n", config);
	return regmap_write(regmap, NANO_CFG, config);
}