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
struct snd_soc_component {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct adau1701 {scalar_t__ dai_fmt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1701_SERICTL ; 
 int /*<<< orphan*/  ADAU1701_SERICTL_MODE_MASK ; 
 unsigned int ADAU1701_SERICTL_RIGHTJ_16 ; 
 unsigned int ADAU1701_SERICTL_RIGHTJ_20 ; 
 unsigned int ADAU1701_SERICTL_RIGHTJ_24 ; 
 int EINVAL ; 
 scalar_t__ SND_SOC_DAIFMT_RIGHT_J ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_set_playback_pcm_format(struct snd_soc_component *component,
					    struct snd_pcm_hw_params *params)
{
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	unsigned int val;

	if (adau1701->dai_fmt != SND_SOC_DAIFMT_RIGHT_J)
		return 0;

	switch (params_width(params)) {
	case 16:
		val = ADAU1701_SERICTL_RIGHTJ_16;
		break;
	case 20:
		val = ADAU1701_SERICTL_RIGHTJ_20;
		break;
	case 24:
		val = ADAU1701_SERICTL_RIGHTJ_24;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adau1701->regmap, ADAU1701_SERICTL,
		ADAU1701_SERICTL_MODE_MASK, val);

	return 0;
}