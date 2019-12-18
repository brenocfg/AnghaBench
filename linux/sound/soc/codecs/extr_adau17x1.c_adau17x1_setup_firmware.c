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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct adau {int /*<<< orphan*/  regmap; TYPE_1__* sigmadsp; } ;
struct TYPE_2__ {unsigned int current_samplerate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU17X1_DSP_ENABLE ; 
 int /*<<< orphan*/  ADAU17X1_DSP_RUN ; 
 int /*<<< orphan*/  ADAU17X1_DSP_SAMPLING_RATE ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sigmadsp_setup (TYPE_1__*,unsigned int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int adau17x1_setup_firmware(struct snd_soc_component *component,
	unsigned int rate)
{
	int ret;
	int dspsr, dsp_run;
	struct adau *adau = snd_soc_component_get_drvdata(component);
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	/* Check if sample rate is the same as before. If it is there is no
	 * point in performing the below steps as the call to
	 * sigmadsp_setup(...) will return directly when it finds the sample
	 * rate to be the same as before. By checking this we can prevent an
	 * audiable popping noise which occours when toggling DSP_RUN.
	 */
	if (adau->sigmadsp->current_samplerate == rate)
		return 0;

	snd_soc_dapm_mutex_lock(dapm);

	ret = regmap_read(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, &dspsr);
	if (ret)
		goto err;

	ret = regmap_read(adau->regmap, ADAU17X1_DSP_RUN, &dsp_run);
	if (ret)
		goto err;

	regmap_write(adau->regmap, ADAU17X1_DSP_ENABLE, 1);
	regmap_write(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, 0xf);
	regmap_write(adau->regmap, ADAU17X1_DSP_RUN, 0);

	ret = sigmadsp_setup(adau->sigmadsp, rate);
	if (ret) {
		regmap_write(adau->regmap, ADAU17X1_DSP_ENABLE, 0);
		goto err;
	}
	regmap_write(adau->regmap, ADAU17X1_DSP_SAMPLING_RATE, dspsr);
	regmap_write(adau->regmap, ADAU17X1_DSP_RUN, dsp_run);

err:
	snd_soc_dapm_mutex_unlock(dapm);

	return ret;
}