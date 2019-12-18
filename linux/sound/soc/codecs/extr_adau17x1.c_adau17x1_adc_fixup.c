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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct adau {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_CONVERTER0 ; 
 int /*<<< orphan*/  ADAU17X1_CONVERTER0_ADOSR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau17x1_adc_fixup(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct adau *adau = snd_soc_component_get_drvdata(component);

	/*
	 * If we are capturing, toggle the ADOSR bit in Converter Control 0 to
	 * avoid losing SNR (workaround from ADI). This must be done after
	 * the ADC(s) have been enabled. According to the data sheet, it is
	 * normally illegal to set this bit when the sampling rate is 96 kHz,
	 * but according to ADI it is acceptable for this workaround.
	 */
	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_ADOSR, ADAU17X1_CONVERTER0_ADOSR);
	regmap_update_bits(adau->regmap, ADAU17X1_CONVERTER0,
		ADAU17X1_CONVERTER0_ADOSR, 0);

	return 0;
}