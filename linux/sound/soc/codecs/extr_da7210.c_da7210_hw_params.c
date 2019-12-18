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
typedef  scalar_t__ u32 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct da7210_priv {scalar_t__ mclk_rate; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7210_DAI_CFG1 ; 
 int /*<<< orphan*/  DA7210_DAI_CFG3 ; 
 scalar_t__ DA7210_DAI_EN ; 
 scalar_t__ DA7210_DAI_OE ; 
 scalar_t__ DA7210_DAI_OUT_L_SRC ; 
 scalar_t__ DA7210_DAI_OUT_R_SRC ; 
 int /*<<< orphan*/  DA7210_DAI_SRC_SEL ; 
 scalar_t__ DA7210_DAI_WORD_S16_LE ; 
 scalar_t__ DA7210_DAI_WORD_S20_3LE ; 
 scalar_t__ DA7210_DAI_WORD_S24_LE ; 
 scalar_t__ DA7210_DAI_WORD_S32_LE ; 
 scalar_t__ DA7210_MCLK_DET_EN ; 
 scalar_t__ DA7210_MCLK_SRM_EN ; 
 int /*<<< orphan*/  DA7210_PLL ; 
 scalar_t__ DA7210_PLL_BYP ; 
 int /*<<< orphan*/  DA7210_PLL_DIV3 ; 
 scalar_t__ DA7210_PLL_FS_11025 ; 
 scalar_t__ DA7210_PLL_FS_12000 ; 
 scalar_t__ DA7210_PLL_FS_16000 ; 
 scalar_t__ DA7210_PLL_FS_22050 ; 
 scalar_t__ DA7210_PLL_FS_32000 ; 
 scalar_t__ DA7210_PLL_FS_44100 ; 
 scalar_t__ DA7210_PLL_FS_48000 ; 
 scalar_t__ DA7210_PLL_FS_8000 ; 
 scalar_t__ DA7210_PLL_FS_88200 ; 
 scalar_t__ DA7210_PLL_FS_96000 ; 
 scalar_t__ DA7210_PLL_FS_MASK ; 
 scalar_t__ DA7210_SC_MST_EN ; 
 int /*<<< orphan*/  DA7210_STARTUP1 ; 
 int EINVAL ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct da7210_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int da7210_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct da7210_priv *da7210 = snd_soc_component_get_drvdata(component);
	u32 dai_cfg1;
	u32 fs, sysclk;

	/* set DAI source to Left and Right ADC */
	snd_soc_component_write(component, DA7210_DAI_SRC_SEL,
		     DA7210_DAI_OUT_R_SRC | DA7210_DAI_OUT_L_SRC);

	/* Enable DAI */
	snd_soc_component_write(component, DA7210_DAI_CFG3, DA7210_DAI_OE | DA7210_DAI_EN);

	dai_cfg1 = 0xFC & snd_soc_component_read32(component, DA7210_DAI_CFG1);

	switch (params_width(params)) {
	case 16:
		dai_cfg1 |= DA7210_DAI_WORD_S16_LE;
		break;
	case 20:
		dai_cfg1 |= DA7210_DAI_WORD_S20_3LE;
		break;
	case 24:
		dai_cfg1 |= DA7210_DAI_WORD_S24_LE;
		break;
	case 32:
		dai_cfg1 |= DA7210_DAI_WORD_S32_LE;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, DA7210_DAI_CFG1, dai_cfg1);

	switch (params_rate(params)) {
	case 8000:
		fs		= DA7210_PLL_FS_8000;
		sysclk		= 3072000;
		break;
	case 11025:
		fs		= DA7210_PLL_FS_11025;
		sysclk		= 2822400;
		break;
	case 12000:
		fs		= DA7210_PLL_FS_12000;
		sysclk		= 3072000;
		break;
	case 16000:
		fs		= DA7210_PLL_FS_16000;
		sysclk		= 3072000;
		break;
	case 22050:
		fs		= DA7210_PLL_FS_22050;
		sysclk		= 2822400;
		break;
	case 32000:
		fs		= DA7210_PLL_FS_32000;
		sysclk		= 3072000;
		break;
	case 44100:
		fs		= DA7210_PLL_FS_44100;
		sysclk		= 2822400;
		break;
	case 48000:
		fs		= DA7210_PLL_FS_48000;
		sysclk		= 3072000;
		break;
	case 88200:
		fs		= DA7210_PLL_FS_88200;
		sysclk		= 2822400;
		break;
	case 96000:
		fs		= DA7210_PLL_FS_96000;
		sysclk		= 3072000;
		break;
	default:
		return -EINVAL;
	}

	/* Disable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1, DA7210_SC_MST_EN, 0);

	snd_soc_component_update_bits(component, DA7210_PLL, DA7210_PLL_FS_MASK, fs);

	if (da7210->mclk_rate && (da7210->mclk_rate != sysclk)) {
		/* PLL mode, disable PLL bypass */
		snd_soc_component_update_bits(component, DA7210_PLL_DIV3, DA7210_PLL_BYP, 0);

		if (!da7210->master) {
			/* PLL slave mode, also enable SRM */
			snd_soc_component_update_bits(component, DA7210_PLL,
						   (DA7210_MCLK_SRM_EN |
						    DA7210_MCLK_DET_EN),
						   (DA7210_MCLK_SRM_EN |
						    DA7210_MCLK_DET_EN));
		}
	} else {
		/* PLL bypass mode, enable PLL bypass and Auto Detection */
		snd_soc_component_update_bits(component, DA7210_PLL, DA7210_MCLK_DET_EN,
						       DA7210_MCLK_DET_EN);
		snd_soc_component_update_bits(component, DA7210_PLL_DIV3, DA7210_PLL_BYP,
							    DA7210_PLL_BYP);
	}
	/* Enable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1,
			    DA7210_SC_MST_EN, DA7210_SC_MST_EN);

	return 0;
}