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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7213_DAI_CTRL ; 
 int /*<<< orphan*/  DA7213_DAI_WORD_LENGTH_MASK ; 
 int /*<<< orphan*/  DA7213_DAI_WORD_LENGTH_S16_LE ; 
 int /*<<< orphan*/  DA7213_DAI_WORD_LENGTH_S20_LE ; 
 int /*<<< orphan*/  DA7213_DAI_WORD_LENGTH_S24_LE ; 
 int /*<<< orphan*/  DA7213_DAI_WORD_LENGTH_S32_LE ; 
 int /*<<< orphan*/  DA7213_SR ; 
 int /*<<< orphan*/  DA7213_SR_11025 ; 
 int /*<<< orphan*/  DA7213_SR_12000 ; 
 int /*<<< orphan*/  DA7213_SR_16000 ; 
 int /*<<< orphan*/  DA7213_SR_22050 ; 
 int /*<<< orphan*/  DA7213_SR_32000 ; 
 int /*<<< orphan*/  DA7213_SR_44100 ; 
 int /*<<< orphan*/  DA7213_SR_48000 ; 
 int /*<<< orphan*/  DA7213_SR_8000 ; 
 int /*<<< orphan*/  DA7213_SR_88200 ; 
 int /*<<< orphan*/  DA7213_SR_96000 ; 
 int EINVAL ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7213_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u8 dai_ctrl = 0;
	u8 fs;

	/* Set DAI format */
	switch (params_width(params)) {
	case 16:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S16_LE;
		break;
	case 20:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S20_LE;
		break;
	case 24:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S24_LE;
		break;
	case 32:
		dai_ctrl |= DA7213_DAI_WORD_LENGTH_S32_LE;
		break;
	default:
		return -EINVAL;
	}

	/* Set sampling rate */
	switch (params_rate(params)) {
	case 8000:
		fs = DA7213_SR_8000;
		break;
	case 11025:
		fs = DA7213_SR_11025;
		break;
	case 12000:
		fs = DA7213_SR_12000;
		break;
	case 16000:
		fs = DA7213_SR_16000;
		break;
	case 22050:
		fs = DA7213_SR_22050;
		break;
	case 32000:
		fs = DA7213_SR_32000;
		break;
	case 44100:
		fs = DA7213_SR_44100;
		break;
	case 48000:
		fs = DA7213_SR_48000;
		break;
	case 88200:
		fs = DA7213_SR_88200;
		break;
	case 96000:
		fs = DA7213_SR_96000;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, DA7213_DAI_CTRL, DA7213_DAI_WORD_LENGTH_MASK,
			    dai_ctrl);
	snd_soc_component_write(component, DA7213_SR, fs);

	return 0;
}