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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max98371_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX98371_CHANNEL_MASK ; 
 int /*<<< orphan*/  MAX98371_DAI_BSEL_32 ; 
 int /*<<< orphan*/  MAX98371_DAI_BSEL_48 ; 
 int /*<<< orphan*/  MAX98371_DAI_BSEL_64 ; 
 int /*<<< orphan*/  MAX98371_DAI_BSEL_MASK ; 
 int /*<<< orphan*/  MAX98371_DAI_CHANNEL ; 
 int /*<<< orphan*/  MAX98371_DAI_CHANSZ_16 ; 
 int /*<<< orphan*/  MAX98371_DAI_CHANSZ_32 ; 
 int /*<<< orphan*/  MAX98371_DAI_CLK ; 
 int /*<<< orphan*/  MAX98371_FMT ; 
 int /*<<< orphan*/  MAX98371_FMT_MASK ; 
 int /*<<< orphan*/  MAX98371_MONOMIX_SRC ; 
 int /*<<< orphan*/  MAX98371_MONOMIX_SRC_MASK ; 
 int /*<<< orphan*/  MAX98371_SPK_SR ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_32 ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_44 ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_48 ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_88 ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_96 ; 
 int /*<<< orphan*/  MAX98371_SPK_SR_MASK ; 
 int /*<<< orphan*/  MONOMIX_RX_0_1 ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S24_LE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_S8 128 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max98371_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98371_dai_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max98371_priv *max98371 = snd_soc_component_get_drvdata(component);
	int blr_clk_ratio, ch_size, channels = params_channels(params);
	int rate = params_rate(params);

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S8:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 8;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 32;
		break;
	default:
		return -EINVAL;
	}

	/* BCLK/LRCLK ratio calculation */
	blr_clk_ratio = channels * ch_size;
	switch (blr_clk_ratio) {
	case 32:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_32);
		break;
	case 48:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_48);
		break;
	case 64:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_64);
		break;
	default:
		return -EINVAL;
	}

	switch (rate) {
	case 32000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_32);
		break;
	case 44100:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_44);
		break;
	case 48000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_48);
		break;
	case 88200:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_88);
		break;
	case 96000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_96);
		break;
	default:
		return -EINVAL;
	}

	/* enabling both the RX channels*/
	regmap_update_bits(max98371->regmap, MAX98371_MONOMIX_SRC,
			MAX98371_MONOMIX_SRC_MASK, MONOMIX_RX_0_1);
	regmap_update_bits(max98371->regmap, MAX98371_DAI_CHANNEL,
			MAX98371_CHANNEL_MASK, MAX98371_CHANNEL_MASK);
	return 0;
}