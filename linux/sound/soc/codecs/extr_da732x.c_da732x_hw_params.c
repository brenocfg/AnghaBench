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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {TYPE_1__* driver; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA732X_AIF_WORD_16 ; 
 int /*<<< orphan*/  DA732X_AIF_WORD_20 ; 
 int /*<<< orphan*/  DA732X_AIF_WORD_24 ; 
 int /*<<< orphan*/  DA732X_AIF_WORD_32 ; 
 int /*<<< orphan*/  DA732X_AIF_WORD_MASK ; 
 int /*<<< orphan*/  DA732X_REG_CLK_CTRL ; 
 int /*<<< orphan*/  DA732X_SR1_MASK ; 
 int /*<<< orphan*/  DA732X_SR_11_025KHZ ; 
 int /*<<< orphan*/  DA732X_SR_12KHZ ; 
 int /*<<< orphan*/  DA732X_SR_16KHZ ; 
 int /*<<< orphan*/  DA732X_SR_22_05KHZ ; 
 int /*<<< orphan*/  DA732X_SR_24KHZ ; 
 int /*<<< orphan*/  DA732X_SR_32KHZ ; 
 int /*<<< orphan*/  DA732X_SR_44_1KHZ ; 
 int /*<<< orphan*/  DA732X_SR_48KHZ ; 
 int /*<<< orphan*/  DA732X_SR_88_1KHZ ; 
 int /*<<< orphan*/  DA732X_SR_8KHZ ; 
 int /*<<< orphan*/  DA732X_SR_96KHZ ; 
 int EINVAL ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da732x_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u32 aif = 0;
	u32 reg_aif;
	u32 fs;

	reg_aif = dai->driver->base;

	switch (params_width(params)) {
	case 16:
		aif |= DA732X_AIF_WORD_16;
		break;
	case 20:
		aif |= DA732X_AIF_WORD_20;
		break;
	case 24:
		aif |= DA732X_AIF_WORD_24;
		break;
	case 32:
		aif |= DA732X_AIF_WORD_32;
		break;
	default:
		return -EINVAL;
	}

	switch (params_rate(params)) {
	case 8000:
		fs = DA732X_SR_8KHZ;
		break;
	case 11025:
		fs = DA732X_SR_11_025KHZ;
		break;
	case 12000:
		fs = DA732X_SR_12KHZ;
		break;
	case 16000:
		fs = DA732X_SR_16KHZ;
		break;
	case 22050:
		fs = DA732X_SR_22_05KHZ;
		break;
	case 24000:
		fs = DA732X_SR_24KHZ;
		break;
	case 32000:
		fs = DA732X_SR_32KHZ;
		break;
	case 44100:
		fs = DA732X_SR_44_1KHZ;
		break;
	case 48000:
		fs = DA732X_SR_48KHZ;
		break;
	case 88100:
		fs = DA732X_SR_88_1KHZ;
		break;
	case 96000:
		fs = DA732X_SR_96KHZ;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_update_bits(component, reg_aif, DA732X_AIF_WORD_MASK, aif);
	snd_soc_component_update_bits(component, DA732X_REG_CLK_CTRL, DA732X_SR1_MASK, fs);

	return 0;
}